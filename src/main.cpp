#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>


#define MAX_BITMASK_VALUE 2147483648 // 0x80000000, esto se puede aumentar teoricamente hasta el limite de uint64_t, pero obviamente ya seria demasiado.

enum BitMaskType
{
    Bitmask_Custom,
    Bitmask_SpellAttr0,
    Bitmask_SpellAttr1,
    Bitmask_SpellAttr2,
    Bitmask_SpellAttr3,
    Bitmask_SpellAttr4,
    Bitmask_SpellAttr5,
    Bitmask_SpellAttr6,
    Bitmask_SpellAttr7,
    Bitmask_SpellAttr8,
    Bitmask_SpellAttr9,
    Bitmask_SpellAttr10,
    Bitmask_UnitTypeMask,
    Bitmask_UnitFlags2,
    Bitmask_UnitFlags,
    Bitmask_SpellClickCastFlags,
    Bitmask_PlayerFlags,
    Bitmask_PlayerFieldByteFlags,
    Bitmask_PlayerFieldByte2Flags,
    Bitmask_PlayerExtraFlags,
    Bitmask_NPCFlags,
    Bitmask_MovementFlags,
    Bitmask_MovementFlags2,
    Bitmask_AtLoginFlags,
};

struct Bitmask
{
    Bitmask(std::string fileName) : stringFile(fileName) {}

    std::string stringFile;
    std::map<uint64_t, std::string> _strings;
};

std::map<BitMaskType, Bitmask*> _storeBitmaskStrings;

void LoadBitmaskString()
{
    for (auto itr : _storeBitmaskStrings)
    {
        boost::filesystem::path p("StringFiles/" + itr.second->stringFile);
        try
        {
            if (boost::filesystem::exists(p))
            {
                std::ifstream file(p.string());
                std::string str;
                uint32_t _lineCount = 1;
                while (std::getline(file, str))
                {
                    boost::char_separator<char> sep("=");
                    boost::tokenizer<boost::char_separator<char> > tokens(str, sep);

                    if (std::distance(tokens.begin(), tokens.end()) != 2)
                    {
                        std::cerr << "Error de formato en el archivo: " << p.string() << ", en la linea: " << _lineCount << std::endl;
                        continue;
                    }

                    boost::tokenizer<boost::char_separator<char> >::iterator token = tokens.begin();

                    std::string maskName = *token++;
                    maskName.erase(std::remove_if(maskName.begin(), maskName.end(), [](char c){ return isspace(c, std::cin.getloc()); }), maskName.end());// Borramos cualquier espacio que tenga
                    std::string hexString = *token++;
                    hexString.erase(std::remove_if(hexString.begin(), hexString.end(), [](char c){ return isspace(c, std::cin.getloc()); }), hexString.end());// Borramos cualquier espacio que tenga

                    // std::cout << maskName << " = " << hexString << std::endl;

                    uint64_t number;
                    std::stringstream ss;
                    ss << std::hex << hexString;
                    ss >> number;

                    itr.second->_strings[number] = maskName;

                    ++_lineCount;
                }
            }
            else
                std::cout << p << " no existe\n";
        }

        catch (const boost::filesystem::filesystem_error& ex)
        {
            std::cout << ex.what() << '\n';
        }
    }
}

void InitBitmaskTypes()
{
    _storeBitmaskStrings[Bitmask_Custom] = new Bitmask("Custom.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr0] = new Bitmask("SpellAttr0.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr1] = new Bitmask("SpellAttr1.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr2] = new Bitmask("SpellAttr2.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr3] = new Bitmask("SpellAttr3.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr4] = new Bitmask("SpellAttr4.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr5] = new Bitmask("SpellAttr5.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr6] = new Bitmask("SpellAttr6.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr7] = new Bitmask("SpellAttr7.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr8] = new Bitmask("SpellAttr8.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr9] = new Bitmask("SpellAttr9.txt");
    _storeBitmaskStrings[Bitmask_SpellAttr10] = new Bitmask("SpellAttr10.txt");
    _storeBitmaskStrings[Bitmask_UnitTypeMask] = new Bitmask("UnitTypeMask.txt");
    _storeBitmaskStrings[Bitmask_UnitFlags2] = new Bitmask("UnitFlags2.txt");
    _storeBitmaskStrings[Bitmask_UnitFlags] = new Bitmask("UnitFlags.txt");
    _storeBitmaskStrings[Bitmask_SpellClickCastFlags] = new Bitmask("SpellClickCastFlags.txt");
    _storeBitmaskStrings[Bitmask_PlayerFlags] = new Bitmask("PlayerFlags.txt");
    _storeBitmaskStrings[Bitmask_PlayerFieldByteFlags] = new Bitmask("PlayerFieldByteFlags.txt");
    _storeBitmaskStrings[Bitmask_PlayerFieldByte2Flags] = new Bitmask("PlayerFieldByte2Flags.txt");
    _storeBitmaskStrings[Bitmask_PlayerExtraFlags] = new Bitmask("PlayerExtraFlags.txt");
    _storeBitmaskStrings[Bitmask_NPCFlags] = new Bitmask("NPCFlags.txt");
    _storeBitmaskStrings[Bitmask_MovementFlags] = new Bitmask("MovementFlags.txt");
    _storeBitmaskStrings[Bitmask_MovementFlags2] = new Bitmask("MovementFlags2.txt");
    _storeBitmaskStrings[Bitmask_AtLoginFlags] = new Bitmask("AtLoginFlags.txt");

    LoadBitmaskString();
}

void DeleteAll()
{
    for (auto itr : _storeBitmaskStrings)
        delete itr.second;

    _storeBitmaskStrings.clear();
}


int main()
{
    InitBitmaskTypes();

    while (true)
    {
        std::cout << "Seleccione el archivo de Bitmask (-1 si no quieres usar ninguno, -2 para salir):" << std::endl;

        for (auto menuItr : _storeBitmaskStrings)
            std::cout << menuItr.first << " - " << menuItr.second->stringFile << std::endl;

        int32_t opcion;
        std::cin >> opcion;

        if (opcion == -2)
            break;

        if (opcion != -1 && _storeBitmaskStrings.find(BitMaskType(opcion)) == _storeBitmaskStrings.end())
        {
            std::cout << "No es una seleccion valida..." << std::endl;
            continue;
        }

        uint64_t testNumber;
        std::cout << "Ingrese el numero que desea verificar: " << std::endl;
        std::cin >> testNumber;

        std::cout << "\n---------------\n";

        for (uint64_t i = 1; i <= uint64_t(MAX_BITMASK_VALUE); i *= 2)
        {
            if (testNumber & i)
            {
                if (opcion == -1)
                    std::cout << "Dec: " << i << " ,Hex: 0x" << std::hex << i << std::dec << std::endl;
                else if (_storeBitmaskStrings[BitMaskType(opcion)]->_strings.find(i) != _storeBitmaskStrings[BitMaskType(opcion)]->_strings.end())
                    std::cout << _storeBitmaskStrings[BitMaskType(opcion)]->_strings[i] << " = Dec: " << i << " ,Hex: 0x" << std::hex << i << std::dec << std::endl;
                else // En caso de que falte en el archivo de strings.
                    std::cout << "No se encontro texto = " << "Dec: " << i << " ,Hex: 0x" << std::hex << i << std::dec << std::endl;
            }
        }

        std::cout << "---------------\n";

        std::cout << "Presione enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }

    DeleteAll();

    return EXIT_SUCCESS;
}
