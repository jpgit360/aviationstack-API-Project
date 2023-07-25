import json

# open main json file (the one I'm merging into)
with open("good.json", "r") as master_json_file:
    # load json file into dictionary object
    master_json_dict = json.load(master_json_file)

# open newly ingested json file
with open("sample.json" ,"r") as ingested_json_file:
    ingested_json_dict = json.load(ingested_json_file)

#test code
test = ingested_json_dict["data"][0]
master_json_dict["data"].append(test)

#create vector to store keys
vec = []

# loop through master dictionary and populate keys vector
for i in master_json_dict["data"]:
    departure_data = i["departure"]["iata"] if i["departure"]["iata"] else ""
    arrival_data = i["arrival"]["iata"] if i["arrival"]["iata"] else ""
    flightnum_data = i["flight"]["number"] if i["flight"]["number"] else ""
    str = departure_data + arrival_data + flightnum_data
    vec.append(str)

with open("bruh.json", "w") as json_file:
    json.dump(master_json_dict, json_file, indent=2)

