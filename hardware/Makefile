default: bom

bom:
  /c/Python27/Scripts/kifield -x fk-core.sch -i fk-core.csv
  cat fk-core.csv | /c/Python27/python.exe group-bom.py > fk-core-grouped.csv
