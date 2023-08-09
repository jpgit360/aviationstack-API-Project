REM Change working directory to the directory of the batch file
cd /d "C:/Users/jfpth/OneDrive/Desktop/aviationstack_api_project/data_ingestion"

REM Run API Request script
python api_request.py

REM Run JSON merge script
python json_merge.py

REM Log the current date and time to a log file
echo %date% %time% - Batch file ran >> logfile.txt