#include "JSON.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

int main() {
    // Créer un objet JSON
    Document document;
    document.SetObject();
    Value nom("John");
    Value age(30);
    Value estEtudiant(false);
    document.AddMember("nom", nom, document.GetAllocator());
    document.AddMember("âge", age, document.GetAllocator());
    document.AddMember("estEtudiant", estEtudiant, document.GetAllocator());

    // Convertir l'objet JSON en chaîne
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    return 0;
}

