model EtapaSecuenciador "N-stage timed process sequencer with sensor confirmation — FMI 2.0 ME"
  parameter Integer N_ETAPAS = 5 "Total number of process stages";
  parameter Real duracion_etapa = 10.0 "Minimum dwell time per stage (s)";
  parameter Real Ts = 0.1 "Sampling period (s). Must be << duracion_etapa";

  Modelica.Blocks.Interfaces.BooleanInput arrancar annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, 50}, {-100, 70}}), iconTransformation(origin = {0, -20}, extent = {{-120, 50}, {-100, 70}})));
  Modelica.Blocks.Interfaces.BooleanInput parar annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, 10}, {-100, 30}}), iconTransformation(origin = {0, -20}, extent = {{-120, 10}, {-100, 30}})));
  Modelica.Blocks.Interfaces.RealInput sensor_confirmacion annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, -30}, {-100, -10}}), iconTransformation(origin = {0, -20}, extent = {{-120, -30}, {-100, -10}})));

  Modelica.Blocks.Interfaces.IntegerOutput etapa_actual annotation(
    Placement(transformation(extent = {{100, 50}, {120, 70}}), iconTransformation(origin = {0, -20}, extent = {{100, 50}, {120, 70}})));
  Modelica.Blocks.Interfaces.IntegerOutput etapa_previa annotation(
    Placement(transformation(extent = {{100, 10}, {120, 30}}), iconTransformation(origin = {0, -20}, extent = {{100, 10}, {120, 30}})));
  Modelica.Blocks.Interfaces.RealOutput progreso_etapa annotation(
    Placement(transformation(extent = {{100, -30}, {120, -10}}), iconTransformation(origin = {0, -20}, extent = {{100, -30}, {120, -10}})));
  Modelica.Blocks.Interfaces.BooleanOutput secuencia_completa annotation(
    Placement(transformation(extent = {{100, -70}, {120, -50}}), iconTransformation(origin = {0, -20}, extent = {{100, -70}, {120, -50}})));

  // All discrete variables — sampled every Ts seconds via sample().
  // Using sampled versions of all inputs breaks every algebraic loop and
  // satisfies the OpenModelica requirement that pre() only applies to
  // discrete expressions.
  discrete Integer etapa(start = 0);
  discrete Integer etapa_ant(start = 0);
  discrete Real t_inicio(start = 0.0);
  discrete Real tiempo_en_etapa(start = 0.0);
  discrete Real sensor_s(start = 0.0)
    "Sampled version of sensor_confirmacion. Updated every Ts seconds";

equation
  when sample(0, Ts) then
    tiempo_en_etapa = time - pre(t_inicio);
    sensor_s        = sensor_confirmacion;
  end when;

  etapa_actual       = etapa;
  etapa_previa       = etapa_ant;
  progreso_etapa     = if pre(etapa) > 0 then min(1.0, pre(tiempo_en_etapa) / duracion_etapa) else 0.0;
  secuencia_completa = pre(etapa) == 0 and pre(etapa_ant) == N_ETAPAS;

algorithm
  when {edge(parar),
        edge(arrancar),
        pre(tiempo_en_etapa) >= duracion_etapa and pre(sensor_s) > 0.5 and pre(etapa) > 0} then
    if edge(parar) then
      etapa     := 0;
      etapa_ant := pre(etapa);
      t_inicio  := time;
    elseif edge(arrancar) and pre(etapa) == 0 then
      etapa     := 1;
      etapa_ant := 0;
      t_inicio  := time;
    elseif pre(tiempo_en_etapa) >= duracion_etapa
           and pre(sensor_s) > 0.5
           and pre(etapa) > 0
           and not edge(parar) then
      etapa_ant := pre(etapa);
      t_inicio  := time;
      if pre(etapa) < N_ETAPAS then
        etapa := pre(etapa) + 1;
      else
        etapa := 0;
      end if;
    end if;
  end when;

  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {250, 248, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {80, 60, 0}, extent = {{-90, 95}, {90, 72}}, textString = "EtapaSecuenciador"), Rectangle(origin = {40, -4},lineColor = {0, 80, 0}, fillColor = {200, 240, 200}, fillPattern = FillPattern.Solid, extent = {{-80, 55}, {-50, 35}}), Text(origin = {40, -4},textColor = {0, 80, 0}, extent = {{-78, 53}, {-52, 37}}, textString = "S1"), Rectangle(origin = {40, -4},lineColor = {0, 80, 0}, fillColor = {200, 240, 200}, fillPattern = FillPattern.Solid, extent = {{-45, 55}, {-15, 35}}), Text(origin = {40, -4},textColor = {0, 80, 0}, extent = {{-43, 53}, {-17, 37}}, textString = "S2"), Rectangle(origin = {40, -4},lineColor = {0, 80, 0}, fillColor = {200, 240, 200}, fillPattern = FillPattern.Solid, extent = {{-10, 55}, {20, 35}}), Text(origin = {40, -4},textColor = {0, 80, 0}, extent = {{-8, 53}, {18, 37}}, textString = "S3"), Line(origin = {40, -4},points = {{-50, 45}, {-45, 45}}, color = {0, 80, 0}, thickness = 1.5), Line(origin = {40, -4},points = {{-15, 45}, {-10, 45}}, color = {0, 80, 0}, thickness = 1.5), Rectangle(origin = {40, -18},fillColor = {220, 220, 220}, fillPattern = FillPattern.Solid, extent = {{-80, 25}, {20, 12}}), Rectangle(origin = {40, -18},fillColor = {0, 180, 80}, fillPattern = FillPattern.Solid, extent = {{-80, 25}, {-30, 12}}), Text(origin = {40, -18},textColor = {0, 80, 0}, extent = {{-78, 10}, {18, 0}}, textString = "PROGRESS"), Line(origin = {0, -20},points = {{-100, 60}, {-81, 60}}, color = {0, 120, 0}), Text(origin = {0, -30},textColor = {0, 120, 0}, extent = {{-98, 72}, {-62, 82}}, textString = "START"), Line(origin = {0, -20},points = {{-100, 20}, {-83, 20}}, color = {180, 0, 0}), Text(origin = {-2, -28},textColor = {180, 0, 0}, extent = {{-98, 30}, {-62, 40}}, textString = "STOP"), Line(origin = {0, -20},points = {{-100, -20}, {-25, -20}}, color = {0, 0, 180}), Text(origin = {70, -34},textColor = {0, 0, 180}, extent = {{-98, -8}, {-52, 2}}, textString = "SENS"), Line(origin = {0, -20},points = {{60, 60}, {100, 60}}, color = {0, 80, 0}), Line(origin = {0, -20},points = {{60, 20}, {100, 20}}, color = {80, 60, 0}), Line(origin = {0, -20},points = {{20, -20}, {100, -20}}, color = {0, 0, 180}), Ellipse(origin = {0, -14}, fillColor = {255, 220, 0}, fillPattern = FillPattern.Solid, extent = {{50, -58}, {70, -78}}), Text(origin = {-24, 4},textColor = {180, 160, 0}, extent = {{72, -60}, {100, -76}}, textString = "DONE"), Line(origin = {0, -16},points = {{70, -66}, {100, -65}}, color = {180, 160, 0})}),
    Documentation(info = "<html>
      <h3>EtapaSecuenciador</h3>
      <p>sensor_confirmacion is sampled into discrete variable sensor_s every
         Ts seconds. pre() is only applied to discrete variables, satisfying
         the OpenModelica constraint.</p>
    </html>"));
end EtapaSecuenciador;
