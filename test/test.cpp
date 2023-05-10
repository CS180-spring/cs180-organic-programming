#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class JSONDatabase {
public:
    JSONDatabase(const std::string& fileName) : fileName_(fileName) {}

    bool save(const Document& doc) {
        // Serialize the JSON document to a string
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string jsonStr = buffer.GetString();

        // Write the JSON string to a file
        std::ofstream outFile(fileName_);
        if (outFile.is_open()) {
            outFile << jsonStr;
            outFile.close();
            return true;
        }
        return false;
    }

    bool load(Document& doc) {
        // Read the JSON string from the file
        std::ifstream inFile(fileName_);
        if (inFile.is_open()) {
            std::string fileStr((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

            // Parse the JSON string into a new document
            doc.Parse(fileStr.c_str());
            inFile.close();
            return true;
        }
        return false;
    }

private:
    std::string fileName_;
};

int main() {
    // Create a JSON document


    // Add some data to the JSON document
    
    std::string fileName;
    std::string objectName;
    int objectCount;
    char choice1;

    std::string keyInput;
    std::string valueInput;

    std::cout << "Create file?(Y or N)";
    std::cin >> choice1;
    
    if(toupper(choice1) == 'N') {"Okay have a nice day! \n";}
    else {
        Document doc;
        doc.SetObject();

        std::cout << "Name of file: ";
        std::cin >> fileName;

        std::cout << "Would you like to add objects to your file?(Y or N)";
        std::cin >> choice1;

        if(toupper(choice1) == 'N') {"Okay have a nice day! \n";}
        else
        {
            std::cout << "Enter ammount of objects to add: ";
            std::cin >> objectCount;
            

            std::cout << "Object Name: ";
            std::cin >> objectName;

            Value person(kObjectType);
            
            for(int i = 0; i >= objectCount; i++)
            {
                std::cout << "Key: ";
                std::cin >> keyInput;
                std::cout << "Value: ";
                std::cin >> valueInput;
                
                char *a = &(keyInput[0]);

                person.AddMember(keyInput, valueInput, doc.GetAllocator());
            }
        }
    }

    /*Value person(kObjectType);
    person.AddMember("name", "John", doc.GetAllocator());
    person.AddMember("age", 30, doc.GetAllocator());
    person.AddMember("city", "New York", doc.GetAllocator());*/
    doc.AddMember("person", person, doc.GetAllocator());

    // Create a JSON database object
    JSONDatabase db("database.json");

    // Save the JSON document to the database
    db.save(doc);

    // Load the JSON document from the database
    Document newDoc;
    db.load(newDoc);

    // Access the data in the new document
    const Value& name = newDoc["person"]["name"];
    const Value& age = newDoc["person"]["age"];
    const Value& city = newDoc["person"]["city"];

    // Print the data to the console
    std::cout << "Name: " << name.GetString() << std::endl;
    std::cout << "Age: " << age.GetInt() << std::endl;
    std::cout << "City: " << city.GetString() << std::endl;

    return 0;
}
