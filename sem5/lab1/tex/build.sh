LATEX_ARGS=-shell-escape

echo ${LATEX_ARGS}
rm -f *.aux *.toc *.out *.log *.bbl *.blg
pdflatex ${LATEX_ARGS} report_01_01.tex
rm -f *.aux *.toc *.out *.log *.bbl *.blg
