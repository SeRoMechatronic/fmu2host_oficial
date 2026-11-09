# Submission checklist

The scientific and software package is prepared for submission, but the items below require author or repository actions and must not be inferred automatically.

## Required before submission

- [ ] Confirm the final author order, spelling, affiliations, postal addresses, and corresponding-author email with every coauthor.
- [ ] Obtain every coauthor's approval of the submitted manuscript and declarations.
- [ ] Add the final funding statement, grant identifiers, CRediT roles, acknowledgements, and conflict-of-interest declaration.
- [ ] Review the retained failure interpretation with the domain authors of the five partial-suite models.
- [ ] Publish the software/data package without the ignored `paper/` directory, build products, or personal paths.
- [ ] Create an immutable release/tag named `article-v1.0` from the exact public software/data contents.
- [ ] Confirm the repository URL in the separately maintained manuscript, then rebuild its PDF.
- [ ] Re-run `tools/collect_evidence.py` from the tagged checkout and confirm that the recorded generator and FMU hashes match the release.
- [ ] Confirm that all bundled OpenModelica/exported-source notices permit redistribution in the chosen repository.
- [ ] Confirm with the institutions that the MIT copyright line correctly reflects software ownership.

## Editorial files

- [x] Elsevier `elsarticle` manuscript source: `paper/main.tex`
- [x] Compiled manuscript: `paper/main.pdf`
- [x] Bibliography: `paper/references.bib`
- [x] Editable/generated figures and figure scripts
- [x] Highlights: `paper/highlights.txt`
- [x] Draft cover letter: `paper/cover_letter.md`
- [ ] Replace bracketed instructions in the cover letter with the authors' final declarations.
- [ ] Enter any journal-requested author statements directly in the submission system.

## Final reproducibility check

From a fresh Windows/MSVC checkout:

```powershell
python tools\regen_all.py
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
python -m unittest discover -s tests -v
$env:FMU2HOST_BUILD_DIR = (Resolve-Path build)
python tools\run_all_tests.py
python tools\run_paired_modes.py
python tools\collect_evidence.py
```

The two scenario runners intentionally return non-zero while retained failures remain; compare their generated summaries with the committed evidence instead of interpreting that status as a compilation failure.

## Claims that must remain bounded

- Do not describe the package as supporting arbitrary FMUs, complete FMI 2.0 event semantics, FMI 3.0, or bare-metal deployment.
- Do not report the retained oracles as an FMI conformance score.
- Do not describe the legacy `CSPuro_SinME` artifact as CS-only: its XML declares both ME and CS.
- Do not claim identical ME and CS behavior; the paired-mode results document different execution outcomes.
- Do not claim that acceptance is guaranteed. The package reduces avoidable technical and reporting risks, while the editorial and peer-review decision remains external.
