import json 
import os
import sys
from jsonhandling import findHighestVersionKey, pullComponentData, generateComponentKeys, keyToComponentName
from handlePullingData import parseOutComponentCxxClass
from cxxHeaderHandling import CxxClass

searchTypes: list[str] = [
    "item/",
    "entity/",
    "block/"
]

stringsManIDontWantToType: list[str] = [
    [
        "file:///data/packages/minecraftBedrock/schema/item/v1.20.50/components/",
        "file:///data/packages/minecraftBedrock/schema/item/"
    ],
    [
        "file:///data/packages/minecraftBedrock/schema/entity/v1.20.60/components/",
        "file:///data/packages/minecraftBedrock/schema/entity/"
    ],
    [
        "file:///data/packages/minecraftBedrock/schema/block/v1.20.60/components/",
        "file:///data/packages/minecraftBedrock/schema/block/"
    ]
] # hardcoded it should be generated by highest version key but i just wanna test this 

def parseOutLatestVersionData(rawJson: str):
    # parse json
    jsonData = json.loads(rawJson)
    # get latest version keys
    # , "/event.json"
    latestVersions = findHighestVersionKey(jsonData, searchTypes, ["/components/_main.json"])
    # print latest version keys
    for version in latestVersions:
        print(version)
    
    # Order of the list is item, entity, block
    componentData: list[list[dict]] = pullComponentData(jsonData, latestVersions, ["item:", "entity:", "block:"])
    keyLists: list[list[str]] = []
    state: int = 0
    for component in componentData:
        Data: list[str] = generateComponentKeys(component, stringsManIDontWantToType[state][0], stringsManIDontWantToType[state][1])
        state += 1
        keyLists.append(Data)

    for keyList in keyLists:
        state = 0
        for key in keyList:
            state += 1
            print(key)
            
        print(state)
    state = 0
    parentList: list[str] = ["item", "entity", "block"]

    components: list[CxxClass] = []

    for largeKeyList in keyLists:
        for componentKey in largeKeyList:
            componentName: str = keyToComponentName(componentKey)
            localComponentData: dict = jsonData[componentKey]
            CxxClassData: CxxClass = parseOutComponentCxxClass(componentName, jsonData, localComponentData, parentList[state])
            if CxxClassData.isValid():
                print(componentKey)
                components.append(CxxClassData)
        state+=1




def main():
    # read path from command line and if it isnt set default to schemas.json
    path = sys.argv[1] if len(sys.argv) > 1 else "schemas.json"
    # check if file exists
    if not os.path.isfile(path):
        print("File not found")
        return
    # open file and read it
    with open(path, "r") as file:
        rawJson = file.read()

    parseOutLatestVersionData(rawJson)


# Python why do u have no implicit main function call :<
if __name__ == "__main__":
    main()
