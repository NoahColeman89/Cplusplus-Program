import re
import string
from collections import Counter  # Use to count items



def ItemSoldList(v):             # Define a function to output a list of all items in the file
    file1 = open(v,'r')          # Open file in read mode
    lines = file1.readlines()    # Read file and create a list of contents
    new_lines = []               # Create empty list to modify contents

    for string in lines:         # Iterate through inital list
        new_string = string.replace("\n", "") # Remove the \n from all items
        new_lines.append(new_string)          # Append alterd items to new list
    
    file1.close()                # Close file
    return new_lines             # Return final list
    
def ItemSoldCounter(v):          # Define function to count items
    itemList = ItemSoldList(v)   # Call list function

    lineCounts = Counter(itemList)  # Count items in list
    
    return lineCounts            # Return count dictionary
    
def ToatlDailyItemFrequency():   # Declare function to display total items frequencies 
    itemsSold = ItemSoldCounter('CS210_Project_Three_Input_File.txt') # Call item counter function

    for key, value in itemsSold.items(): # Iterate through dictionary, output values
        print("{:<15} {:>5}".format(key, value))


    

def SingleItemFrequency(userItem): # Declare function to find single item frequency
    itemList = ItemSoldList('CS210_Project_Three_Input_File.txt')  # Access item list
    counts = ItemSoldCounter('CS210_Project_Three_Input_File.txt') # Acess item counts

    searchItem = userItem.lower()  # Make userItem lowercase for search purposes
    countItem = searchItem.capitalize()
  
    for i in range(len(itemList)): # Make the itemList lowercase for easy searching
        itemList[i] = itemList[i].lower()
    
    if searchItem in itemList:     # If search item in the list output the amount sold
        print(counts[countItem], countItem, "sold today.")
    else:                          # If the search item is not found output not found
        print("Item not found")

    return 0


def CreateFreqFile():              # Declare function to write a new file
    counts = ItemSoldCounter('CS210_Project_Three_Input_File.txt')  # Acess item counts

    with open("frequency.dat", 'w') as f: # Write dictionary to new file
        for key, value in counts.items(): 
            f.write('%s  %s\n' % (key, value))
 
    f.close()                       # Close the file



