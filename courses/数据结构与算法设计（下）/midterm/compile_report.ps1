Set-Location $PSScriptRoot

xelatex -interaction=nonstopmode report.tex
xelatex -interaction=nonstopmode report.tex

Remove-Item report.aux, report.log, report.out, report.toc -ErrorAction SilentlyContinue

Write-Host "report.pdf 已更新"
