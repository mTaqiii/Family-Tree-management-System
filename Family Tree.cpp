#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>

using namespace std;
// Forward Declaration as in Global Variables we use familyTree and HistoryNode
struct Person;
struct FamilyTree;
struct HistoryNode;
struct FromFamily;
struct ExtendFamily;
/*==========================================================
                    GLOBAL VARIABLES
==========================================================*/

/* Unique Person IDs */
int nextPersonID = 1;

/* Unique Family Tree IDs */
int nextTreeID = 1;

/* Head of the Family Forest (Linked List of Trees) */
FamilyTree* familyForestHead = nullptr;

/* Navigation History Stack */
HistoryNode* historyTop = nullptr;


/*==========================================================
                    RESULT STATUS
==========================================================*/

enum Result
{
    SUCCESS,

    PERSON_NULL,

    PERSON_NOT_FOUND,

    PERSON_DECEASED,

    INVALID_GENDER,

    SAME_PERSON,

    ALREADY_EXISTS,

    DUPLICATE_CHILD,

    DUPLICATE_RELATION,

    TREE_ALREADY_EXISTS,

    RELATIONSHIP_NOT_ALLOWED,

    CANCELLED,

    OPERATION_CANCELLED,

    UNKNOWN_ERROR
};

/*==========================================================
                    Life STATUS
==========================================================*/
enum LifeStatus
{
    ALIVE,
    DECEASED
};

/*==========================================================
                    CONSTANTS
==========================================================*/

const int MAX_NAME_LENGTH = 100;

const string MALE = "male" ;

const string FEMALE = "female" ;

/*==========================================================
                    STRUCTURE DECLARATIONS
==========================================================*/

/*---------------- Family Relations ----------------*/

struct FromFamily
{
    Person* father;
    Person* mother;

    FromFamily()
    {
        father = nullptr;
        mother = nullptr;
    }
};

/* Early we were using only FisrtChild Pointer and accessing other children 

Father (Ahmed)

firstChild
     |
     V
+------+     +------+     +------+     +------+
| Ali  | --> | Sara | --> | Omar | --> | Zain | --> nullptr
+------+     +------+     +------+     +------+
 but if we have to add another child it will take 0(n) time Complexity as it moves from ALi->Sara->Omar->Zain and then add
 Now we are using 2 pointers First and lastChild as it takes 0(1) by directly accessing lastChild

                  Ahmed
              /          \
     firstChild         lastChild
          |                 |
          V                 V

         Ali --> Sara --> Omar --> Zain
 */
struct ExtendFamily
{
    Person* spouse;

    Person* firstChild;

    Person* lastChild;

    ExtendFamily()
    {
        spouse = nullptr;
        firstChild = nullptr;
        lastChild = nullptr;
    }
};


struct Person
{
    int id;
    string name;
    string gender;

    FromFamily fromFamily;
    ExtendFamily extendFamily;

    Person* leftSibling;
    Person* rightSibling;

    LifeStatus status;

    bool visited;

   Person()
    : id(0),
      name(""),
      gender(""),
      fromFamily(),
      extendFamily(),
      leftSibling(nullptr),
      rightSibling(nullptr),
      status(ALIVE),
      visited(false)
    {
    }

};


/*---------------- Family Tree Linked List ----------------*/

struct FamilyTree
{
    int treeID;

    Person* root;

    FamilyTree* next;

    FamilyTree()
    {
        treeID = 0;
        root = nullptr;
        next = nullptr;
    }
};

struct HistoryNode
{
    Person* currentPerson;
    HistoryNode* next;

    HistoryNode()
    {
        currentPerson = nullptr;
        next = nullptr;
    }
};

struct SearchNode
{
    Person* person;

    SearchNode* next;

    SearchNode()
    {
        person = nullptr;
        next = nullptr;
    }
};

//Functions


Result createTreeForPerson(Person* root);   




/*==========================================================
                INPUT UTILITY FUNCTIONS
==========================================================*/
void printResult(Result result);

int inputInteger();

int inputChoice(int min,
                int max,
                const string& prompt)
{
    int choice;

    while (true)
    {
        cout << prompt;

        choice = inputInteger();

        if(choice >= min && choice <= max)
            return choice;

        cout << "Invalid choice! Enter a value between "
             << min << " and " << max << ".\n";
    }
}
string inputName();

string toLowerCase(const string& text);
string inputGender();
char inputYesNo();

void askOpenPersonMenu(Person* person, Person* cameFrom = nullptr);

char askCreateTree()
{
    char choice;

    while(true)
    {
        cout << "\nCreate a new Family Tree for this Person? (Y/N): ";

        cin >> choice;

        choice = toupper(choice);

        if(choice == 'Y' || choice == 'N')
            return choice;

        cout << "\nInvalid Choice!\n";
    }
}

string getLifeStatusString(LifeStatus status)
{
    if(status == ALIVE)
        return "Alive";

    return "Deceased";
}

/*==========================================================
                PERSON HELPER FUNCTIONS
==========================================================*/

int generatePersonID();

int generateTreeID();
bool isMale(const Person* person);
bool isFemale(const Person* person);
Result establishParentRelationship(Person* child,
                                   Person* parent);

/*==========================================================
                VALIDATION FUNCTIONS
==========================================================*/

bool isSamePerson(const Person* first,
                  const Person* second);

bool hasFather(const Person* child);

bool hasMother(const Person* child);

bool hasSpouse(const Person* person);

bool hasChildren(Person* person);

bool childAlreadyExists(const Person* parent,
                        const Person* child);

bool validFather(const Person* father);

bool validMother(const Person* mother);

int inputMenuChoice(int minChoice,
                    int maxChoice);

/*==========================================================
                FAMILY FOREST MANAGER
==========================================================*/

int generateTreeID();

Result validateTreeCreation(Person* root);

FamilyTree* createFamilyTree(Person* root);

Result addTree(FamilyTree* tree);

FamilyTree* findTreeByID(int treeID);

FamilyTree* findTreeByRoot(Person* root);

int countTrees();

bool alreadyRoot(Person* person);

void printAllTrees();


/*==========================================================
                    PERSON MANAGER
==========================================================*/

Person* createPerson(const string& name,
                     const string& gender);

Result destroyPerson(Person* person);

void printPersonSummary(const Person* person);

void printPersonDetailed(const Person* person);

Result renamePerson(Person* person);

Result markPersonDeceased(Person* person);

/*==========================================================
                RELATIONSHIP MANAGER
==========================================================*/

Result assignFather(Person* child,
                    Person* father);

Result assignMother(Person* child,
                    Person* mother);

Result connectSpouses(Person* husband,
                      Person* wife);

Result disconnectSpouses(Person* person);

Result addChildToParent(Person* parent,
                        Person* child);



Result resolveExistingMarriage(Person* person);

Result linkExistingFather(Person* child);

Result linkExistingMother(Person* child);

Result linkExistingSpouse(Person* person);

char askCreateTree();

/*==========================================================
                CHILD REGISTRATION
==========================================================*/

Result validateChildRegistration(
        Person* parent,
        Person* child);

Result createChild(Person* parent);

Result assignParents(
        Person* child,
        Person* parent);
/*==========================================================
                SPOUSE REGISTRATION
==========================================================*/
Result validateSpouseRegistration(
        Person* person,
        Person* spouse);

Result createSpouse(Person* person);

/*==========================================================
                SEARCH MANAGER
==========================================================*/

void searchMenu();

void searchByID();

void searchByName();

Person* findPersonByID(int id);

Person* findPersonsByName(
        const string& name);

Person* findPersonByIDRecursive(
            Person* current,
            int id,
            SearchNode*& visitedHead,
            SearchNode*& visitedTail);

void findPersonsByNameRecursive(
        Person* current,
        const string& name,
        SearchNode*& head,
        SearchNode*& tail,
        SearchNode*& visitedHead,
        SearchNode*& visitedTail);

void addSearchResult(
        SearchNode*& head,
        SearchNode*& tail,
        Person* person);

void destroySearchResults(
        SearchNode*& head);
            
Person* findExistingPerson();

void printSearchResults(
        SearchNode* head);

Person* chooseSearchResult(
        SearchNode* head);
/*==========================================================
                TREE VIEW MANAGER
==========================================================*/
void viewFamilyTree();

void printFamilyTree(Person* root);

void printPersonRecursive(
        Person* person,
        string prefix,
        bool isLast);

/*==========================================================
                PARENT REGISTRATION
==========================================================*/

Result registerFather(Person* child);

Result registerMother(Person* child);

Result createFather(Person* child);

Result createMother(Person* child);

Result validateFatherRegistration(Person* child,Person* father);

Result validateMotherRegistration(Person* child,Person* mother);

/*==========================================================
            FAMILY TREE REGISTRATION FUNCTIONS
==========================================================*/

void registerNewFamilyTree();

void registerRelationshipMenu(Person* person);

// void registerParents(Person* person);

Result registerSpouse(Person* person);

// void registerChildren(Person* person);

/*==========================================================
                VIEW FUNCTIONS
==========================================================*/

void personMenu(Person*& currentPerson);

Person* viewParents(Person* person);

Person* viewChildren(Person* person);

Person* viewSiblings(Person* person);

Person* viewSpouse(Person* person);
/*==========================================================
                Update Person menu
==========================================================*/

void updatePersonMenu(Person* person);

Result updatePersonName(Person* person);

Result updateLifeStatus(Person* person);

Result divorcePerson(Person* person);

/*==========================================================
                DELETE FUNCTIONS
==========================================================*/

void deleteFamilyTree(FamilyTree* tree);
Result removeTreeFromForest(
        FamilyTree* tree);

void deleteTreeMenu();
/*==========================================================
                XML FUNCTIONS
==========================================================*/

string escapeXML(string text);

void createXML();

void writeXML(Person* person,
              ofstream& file,
              int indentation);

void writeIndentation(ofstream& file,
                      int indentation)
{
    for(int i = 0; i < indentation; i++)
        file << ' ';
}

/*==========================================================
                HISTORY STACK FUNCTIONS
==========================================================*/

void pushHistory(Person* person);

Person* popHistory();

Person* peekHistory();

bool isHistoryEmpty();

void clearHistory();
/*==========================================================
                MEMORY CLEANUP
==========================================================*/

void freePerson(Person* person);

void freeAllTrees();

/*==========================================================
                    MAIN MENU
==========================================================*/

void displayMainMenu();

/*==========================================================
                        MAIN
==========================================================*/

int main()
{
    int choice;

    do
    {
        displayMainMenu();

        choice = inputChoice(
                    0,
                    5,
                    "Enter Choice: "
                 );

        switch(choice)
        {
            case 1:

                registerNewFamilyTree();

                break;

            case 2:

                searchMenu();

                break;

            case 3:

                viewFamilyTree();

                break;

            case 4:

                createXML();

                break;

            case 5:

                deleteTreeMenu();

                break;

            case 0:

                break;
        }

    }while(choice != 0);

    //====================================
    // Program Cleanup
    //====================================

    clearHistory();

    freeAllTrees();

    cout << "\nThank you for using Family Tree Management System.\n";

    return 0;
}
/*==========================================================
                TEMPORARY STUB FUNCTIONS
==========================================================*/

int inputInteger()
{
    int value;

    while (true)
    {
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input! Please enter an integer: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string inputName()
{
    string name;

    while (true)
    {
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
            continue;
        }

        bool valid = true;

        for (char c : name)
        {
            if (!(isalpha(c) ||
                  c == ' ' ||
                  c == '\'' ||
                  c == '-'))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            cout << "Invalid name! Only alphabets, spaces, apostrophe (') and hyphen (-) are allowed.\n";
            continue;
        }

        return name;
    }
}

string toLowerCase(const string& text)
{
    string result = text;

    for(char& c : result)
    {
        c = tolower(static_cast<unsigned char>(c));
    }

    return result;
}

string inputGender()
{
    string gender;

    while (true)
    {
        getline(cin, gender);

        for (char &c : gender)
        {
            c = tolower(c);
        }

        if (gender == MALE || gender == FEMALE)
        {
            return gender;
        }

        cout << "Invalid gender! Please enter only 'male' or 'female'.\n";
    }
}

char inputYesNo()
{
    char choice;

    while (true)
    {
        cout << "(Y/N): ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        choice = tolower(choice);

        if (choice == 'y' || choice == 'n' || choice == 'Y' || choice == 'N' )
        {
            return choice;
        }

        cout << "Invalid input! Please enter Y or N.\n";
    }
}

int generateTreeID()
{
    return nextTreeID++;
}

int generatePersonID()
{
    return nextPersonID++;
}

bool isMale(const Person* person)
{
    if(person == nullptr)
        return false;

    return person->gender == MALE;
}

bool isFemale(const Person* person)
{
    if(person == nullptr)
        return false;

    return person->gender == FEMALE;
}

void registerNewFamilyTree()
{
    cout << "\n=====================================\n";
    cout << "     REGISTER NEW FAMILY TREE\n";
    cout << "=====================================\n";
    cout<<"Enter Name : ";
    string name = inputName();
    cout<<"Gender : "; 
    string gender = inputGender();

    Person* root = createPerson(name,gender);

Result validationResult =
    validateTreeCreation(root);

if(validationResult != SUCCESS)
{
    printResult(validationResult);

    destroyPerson(root);

    return;
}

FamilyTree* tree =
createFamilyTree(root);

    if(tree == nullptr)
{
    destroyPerson(root);
    return;
}

    Result addTreeResult = addTree(tree);

    if(addTreeResult == SUCCESS)
    {
        cout << "\nFamily Tree Created Successfully.\n";

        cout << "Tree ID : "
             << tree->treeID
             << endl;

        printPersonDetailed(root);
        askOpenPersonMenu(root);
    }
}

void registerRelationshipMenu(Person* person)
{
    if(person == nullptr)
        return;

    while(true)
    {
        cout << "\n=====================================\n";
        cout << "      REGISTER RELATIONSHIPS\n";
        cout << "=====================================\n";

        cout << "Current Person : "
             << person->name
             << " (ID : "
             << person->id
             << ")\n\n";

        cout << "1. Register Father\n";
        cout << "2. Register Mother\n";
        cout << "3. Register Spouse\n";
        cout << "4. Register Child\n";
        cout << "5. Back\n\n";

        int choice =
            inputChoice(
                1,
                5,
                "Enter Choice: "
            );

        Result result;

        switch(choice)
        {
            case 1:

                result = registerFather(person);

                printResult(result);

                break;

            case 2:

                result = registerMother(person);

                printResult(result);

                break;

            case 3:

                result = registerSpouse(person);

                printResult(result);

                break;

            case 4:

                result = createChild(person);

                printResult(result);

                break;

            case 5:

                return;
        }
    }
}

Result assignFather(Person* child,
                    Person* father)
{
    if(child == nullptr || father == nullptr)
        return PERSON_NULL;

    if(child->fromFamily.father != nullptr)
        return ALREADY_EXISTS;

    if(isSamePerson(child,father))
        return SAME_PERSON;

    if(father->gender != MALE)
        return INVALID_GENDER;

    child->fromFamily.father = father;

    return SUCCESS;
}

Result assignMother(Person* child,
                    Person* mother)
{
    if(child == nullptr || mother == nullptr)
        return PERSON_NULL;

    if(child->fromFamily.mother != nullptr)
        return ALREADY_EXISTS;

    if(isSamePerson(child,mother))
        return SAME_PERSON;

    if(mother->gender != FEMALE)
        return INVALID_GENDER;

    child->fromFamily.mother = mother;

    return SUCCESS;
}

Result connectSpouses(Person* husband,
                      Person* wife)
{
    if(husband == nullptr || wife == nullptr)
        return PERSON_NULL;

    if(isSamePerson(husband,wife))
        return SAME_PERSON;

    if(husband->gender != MALE)
        return INVALID_GENDER;

    if(wife->gender != FEMALE)
        return INVALID_GENDER;

    if(husband->extendFamily.spouse != nullptr)
        return ALREADY_EXISTS;

    if(wife->extendFamily.spouse != nullptr)
        return ALREADY_EXISTS;

    husband->extendFamily.spouse = wife;
    wife->extendFamily.spouse = husband;

    return SUCCESS;
}

Result disconnectSpouses(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    Person* spouse =
        person->extendFamily.spouse;

    if(spouse == nullptr)
        return PERSON_NOT_FOUND;

    spouse->extendFamily.spouse = nullptr;

    person->extendFamily.spouse = nullptr;

    return SUCCESS;
}


Result addChildToParent(Person* parent,
                        Person* child)
{
    if(parent == nullptr || child == nullptr)
        return PERSON_NULL;

    if(parent == child)
        return SAME_PERSON;

    if(childAlreadyExists(parent, child))
        return DUPLICATE_CHILD;

    child->leftSibling = nullptr;
    child->rightSibling = nullptr;

    if(parent->extendFamily.firstChild == nullptr)
    {
        parent->extendFamily.firstChild = child;
        parent->extendFamily.lastChild = child;

        return SUCCESS;
    }

    Person* last = parent->extendFamily.lastChild;

    last->rightSibling = child;

    child->leftSibling = last;

    parent->extendFamily.lastChild = child;

    return SUCCESS;
}

bool isSamePerson(const Person* first,
                  const Person* second)
{
    if(first == nullptr || second == nullptr)
        return false;

    return first->id == second->id;
}

bool hasFather(const Person* child)
{
    if(child == nullptr)
        return false;

    return child->fromFamily.father != nullptr;
}

bool hasMother(const Person* child)
{
    if(child == nullptr)
        return false;

    return child->fromFamily.mother != nullptr;
}

bool hasSpouse(const Person* person)
{
    if(person == nullptr)
        return false;

    return person->extendFamily.spouse != nullptr;
}

bool hasChildren(Person* person)
{
    if(person == nullptr)
        return false;

    return person->extendFamily.firstChild != nullptr;
}

bool childAlreadyExists(const Person* parent,
                        const Person* child)
{
    if(parent == nullptr || child == nullptr)
        return false;

    Person* current = parent->extendFamily.firstChild;

    while(current != nullptr)
    {
        if(current->id == child->id)
            return true;

        current = current->rightSibling;
    }

    return false;
}

bool validFather(const Person* father)
{
    return isMale(father);
}

bool validMother(const Person* mother)
{
    return isFemale(mother);
}

FamilyTree* createFamilyTree(Person* root)
{
    FamilyTree* tree = new FamilyTree;

    tree->root = root;
    tree->next = nullptr;
    tree->treeID = generateTreeID();

    return tree;
}

Result validateTreeCreation(Person* root)
{
    if(root == nullptr)
        return PERSON_NULL;

    if(root->status == DECEASED)
        return PERSON_DECEASED;

    if(alreadyRoot(root))
        return ALREADY_EXISTS;

    return SUCCESS;
}

Result addTree(FamilyTree* tree)
{
    if(tree == nullptr)
        return PERSON_NULL;

    if(familyForestHead == nullptr)
    {
        familyForestHead = tree;
        return SUCCESS;
    }

    FamilyTree* current = familyForestHead;

    while(current->next != nullptr)
    {
        current = current->next;
    }

    current->next = tree;

    return SUCCESS;
}

FamilyTree* findTreeByID(int treeID)
{
    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        if(current->treeID == treeID)
            return current;

        current = current->next;
    }

    return nullptr;
}

FamilyTree* findTreeByRoot(Person* root)
{
    if(root == nullptr)
        return nullptr;

    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        if(current->root == root)
            return current;

        current = current->next;
    }

    return nullptr;
}

int countTrees()
{
    int count = 0;

    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        count++;

        current = current->next;
    }

    return count;
}

bool alreadyRoot(Person* person)
{
    if(person == nullptr)
        return false;

    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        if(current->root == person)
            return true;

        current = current->next;
    }

    return false;
}

void printAllTrees()
{
    if(familyForestHead == nullptr)
    {
        cout << "\nNo Family Trees Available.\n";
        return;
    }

    FamilyTree* current = familyForestHead;

    cout << "\n============= FAMILY FOREST =============\n";

    while(current != nullptr)
    {
        cout << "\nTree ID : " << current->treeID << endl;

        if(current->root != nullptr)
        {
            cout << "Root ID : " << current->root->id << endl;
            cout << "Root Name : " << current->root->name << endl;
        }

        current = current->next;
    }

    cout << "=========================================\n";
}

Person* createPerson(const string& name,
                     const string& gender)
{
    Person* newPerson = new Person();

    newPerson->id = generatePersonID();
    newPerson->name = name;
    newPerson->gender = gender;

    return newPerson;
}

Result destroyPerson(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    delete person;

    return SUCCESS;
}

void printResult(Result result)
{
    switch(result)
    {
    case SUCCESS:
        cout << "Operation completed successfully.\n";
        break;

    case PERSON_NULL:
        cout << "Error: Person is null.\n";
        break;

    case PERSON_NOT_FOUND:
        cout << "Error: Person not found.\n";
        break;

    case PERSON_DECEASED:
        cout << "Error: Operation cannot be performed because the person is deceased.\n";
        break;

    case INVALID_GENDER:
        cout << "Error: Invalid gender.\n";
        break;

    case SAME_PERSON:
        cout << "Error: A person cannot have a relationship with themselves.\n";
        break;

    case ALREADY_EXISTS:
        cout << "Error: Relationship already exists.\n";
        break;

    case DUPLICATE_CHILD:
        cout << "Error: Child is already linked.\n";
        break;

    case OPERATION_CANCELLED:

    cout<<"Operation cancelled.\n";

    break;

    default:
        cout << "Unknown error.\n";
    }
}

void printPersonSummary(const Person* person)
{
    if(person == nullptr)
        return;

    cout << person->id
         << " - "
         << person->name
         << endl;
}

void printPersonDetailed(const Person* person)
{
    if(person == nullptr)
    {
        cout << "\nPerson not found.\n";
        return;
    }

    cout << "\n---------------------------------\n";

    cout << "ID : "
         << person->id
         << endl;

    cout << "Name : "
         << person->name
         << endl;

    cout << "Gender : "
         << person->gender
         << endl;
    
    cout << "Status : "
         << getLifeStatusString(person->status)
         << endl;

    cout << "---------------------------------\n";
}

Result validateFatherRegistration(Person* child,
                                  Person* father)
{
    if(child == nullptr || father == nullptr)
        return PERSON_NULL;

    if(isSamePerson(child, father))
        return SAME_PERSON;

     if(father->status == DECEASED)
        return PERSON_DECEASED;

    if(hasFather(child))
        return ALREADY_EXISTS;

    if(!validFather(father))
        return INVALID_GENDER;

    return SUCCESS;
}

Result registerFather(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    cout << "\n=====================================\n";
    cout << "        REGISTER FATHER\n";
    cout << "=====================================\n";

    cout << "1. Create New Father\n";
    cout << "2. Link Existing Father\n";
    cout << "3. Back\n\n";

    int choice = inputChoice(1,3, "Enter Choice : ");

    switch(choice)
    {
        case 1:
            return createFather(child);

        case 2:
            return linkExistingFather(child);

        case 3:
            return OPERATION_CANCELLED;
    }

    return UNKNOWN_ERROR;
}

Result createFather(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    cout << "\nEnter Father's Name: ";

    string name = inputName();

    Person* father = createPerson(name, MALE);

    Result result = validateFatherRegistration(child, father);

    if(result != SUCCESS)
    {
        destroyPerson(father);
        return result;
    }

    result = assignFather(child, father);

    if(result != SUCCESS)
    {
        destroyPerson(father);
        return result;
    }

    result = addChildToParent(father, child);

    if(result != SUCCESS)
    {
        child->fromFamily.father = nullptr;

        destroyPerson(father);

        return result;
    }

   if(askCreateTree() == 'Y')
    {
    Result result =
        createTreeForPerson(father);

    if(result != SUCCESS)
        return result;
    }

    askOpenPersonMenu(father, child);

    return SUCCESS;
}

Result linkExistingFather(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    Person* father =
        findExistingPerson();

    if(father == nullptr)
        return OPERATION_CANCELLED;

    Result result =
        validateFatherRegistration(
            child,
            father);

    if(result != SUCCESS)
        return result;

    result =
        assignFather(
            child,
            father);

    if(result != SUCCESS)
        return result;

    result =
        addChildToParent(
            father,
            child);

    if(result != SUCCESS)
    {
        child->fromFamily.father = nullptr;

        return result;
    }

    return SUCCESS;
}

Result registerMother(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    cout << "\n=====================================\n";
    cout << "        REGISTER MOTHER\n";
    cout << "=====================================\n";

    cout << "1. Create New Mother\n";
    cout << "2. Link Existing Mother\n";
    cout << "3. Back\n\n";

    int choice = inputChoice(
                    1,
                    3,
                    "Enter Choice: "
                 );

    switch(choice)
    {
        case 1:
            return createMother(child);

        case 2:
            return linkExistingMother(child);

        case 3:
            return OPERATION_CANCELLED;
    }

    return UNKNOWN_ERROR;
}

Result validateMotherRegistration(
        Person* child,
        Person* mother)
{
    if(child == nullptr || mother == nullptr)
        return PERSON_NULL;

    if(isSamePerson(child, mother))
        return SAME_PERSON;

    if(mother->status == DECEASED)
        return PERSON_DECEASED;

    if(hasMother(child))
        return ALREADY_EXISTS;

    if(!validMother(mother))
        return INVALID_GENDER;

    return SUCCESS;
}

Result createMother(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    cout << "\nEnter Mother's Name: ";

    string name = inputName();

    Person* mother = createPerson(name, FEMALE);

    Result result =
        validateMotherRegistration(child, mother);

    if(result != SUCCESS)
    {
        destroyPerson(mother);
        return result;
    }

    result = assignMother(child, mother);

    if(result != SUCCESS)
    {
        destroyPerson(mother);
        return result;
    }

    result = addChildToParent(mother, child);

    if(result != SUCCESS)
    {
        child->fromFamily.mother = nullptr;

        destroyPerson(mother);

        return result;
    }

   if(askCreateTree() == 'Y')
    {
      Result result = createTreeForPerson(mother);

      if(result != SUCCESS)
         return result;
    }
    askOpenPersonMenu(mother, child);
    return SUCCESS;
}

Result linkExistingMother(Person* child)
{
    if(child == nullptr)
        return PERSON_NULL;

    Person* mother =
        findExistingPerson();

    if(mother == nullptr)
        return OPERATION_CANCELLED;

    Result result =
        validateMotherRegistration(
            child,
            mother);

    if(result != SUCCESS)
        return result;

    result =
        assignMother(
            child,
            mother);

    if(result != SUCCESS)
        return result;

    result =
        addChildToParent(
            mother,
            child);

    if(result != SUCCESS)
    {
        child->fromFamily.mother = nullptr;

        return result;
    }

    return SUCCESS;
}

Result validateSpouseRegistration(
        Person* person,
        Person* spouse)
{
    if(person == nullptr || spouse == nullptr)
        return PERSON_NULL;

    if(isSamePerson(person, spouse))
        return SAME_PERSON;

    if(person->status == DECEASED)
        return PERSON_DECEASED;

    if(spouse->status == DECEASED)
        return PERSON_DECEASED;

    if(hasSpouse(person))
        return ALREADY_EXISTS;

    if(hasSpouse(spouse))
        return ALREADY_EXISTS;

    if(isMale(person) && !isFemale(spouse))
        return INVALID_GENDER;

    if(isFemale(person) && !isMale(spouse))
        return INVALID_GENDER;

    return SUCCESS;
}


Result resolveExistingMarriage(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    if(!hasSpouse(person))
        return SUCCESS;

    Person* spouse = person->extendFamily.spouse;

    cout << "\n"
         << person->name
         << " is already married to "
         << spouse->name
         << ".\n\n";

    cout << "Choose an option:\n\n";

    cout << "1. "
         << spouse->name
         << " is deceased. End the marriage.\n";

    cout << "2. "
         << person->name
         << " and "
         << spouse->name
         << " are divorced. End the marriage.\n";

    cout << "3. Cancel.\n\n";

    int choice =
        inputChoice(
            1,
            3,
            "Enter Choice: "
        );

    switch(choice)
    {
        case 1:
            markPersonDeceased(spouse);
            disconnectSpouses(person);
            return SUCCESS;
        case 2:
            disconnectSpouses(person);
            return SUCCESS;
        case 3:
            return OPERATION_CANCELLED;
    }
    return UNKNOWN_ERROR;
}

Result registerSpouse(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    cout << "\n=====================================\n";
    cout << "       REGISTER SPOUSE\n";
    cout << "=====================================\n";

    cout << "1. Create New Spouse\n";
    cout << "2. Link Existing Spouse\n";
    cout << "3. Back\n\n";

    int choice =
        inputChoice(
            1,
            3,
            "Enter Choice: "
        );

    switch(choice)
    {
        case 1:
            return createSpouse(person);

        case 2:
            return linkExistingSpouse(person);

        case 3:
            return OPERATION_CANCELLED;
    }

    return UNKNOWN_ERROR;
}

Result createSpouse(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    cout << "\nEnter Spouse Name: ";

    string name = inputName();

    string gender;

    if(isMale(person))
        gender = FEMALE;
    else
        gender = MALE;

    Person* spouse =
        createPerson(name, gender);

    Result result =
        validateSpouseRegistration(
            person,
            spouse
        );

    if(result == ALREADY_EXISTS)
    {
        result =
            resolveExistingMarriage(person);

        if(result != SUCCESS)
        {
            destroyPerson(spouse);
            return result;
        }
    }
    else if(result != SUCCESS)
    {
        destroyPerson(spouse);
        return result;
    }

    result =
        connectSpouses(
            person,
            spouse
        );

    if(result != SUCCESS)
    {
        destroyPerson(spouse);
        return result;
    }
    if(askCreateTree() == 'Y')
    {
     Result result = createTreeForPerson(spouse);

     if(result != SUCCESS)
         return result;
    }
    askOpenPersonMenu(spouse, person);
    return SUCCESS;
}

Result linkExistingSpouse(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    Person* spouse =
        findExistingPerson();

    if(spouse == nullptr)
        return OPERATION_CANCELLED;

    Result result =
        validateSpouseRegistration(
            person,
            spouse);

    if(result == ALREADY_EXISTS)
    {
        result =
            resolveExistingMarriage(person);

        if(result != SUCCESS)
            return result;
    }
    else if(result != SUCCESS)
    {
        return result;
    }

    result =
        connectSpouses(
            person,
            spouse);

    return result;
}


Result validateChildRegistration(
        Person* parent,
        Person* child)
{
    if(parent == nullptr || child == nullptr)
        return PERSON_NULL;

    if(isSamePerson(parent, child))
        return SAME_PERSON;

    if(parent->status == DECEASED)
        return PERSON_DECEASED;

    if(child->status == DECEASED)
        return PERSON_DECEASED;

    if(childAlreadyExists(parent, child))
        return DUPLICATE_CHILD;

    return SUCCESS;
}

Result assignParents(Person* child,
                     Person* parent)
{
    if(child == nullptr || parent == nullptr)
        return PERSON_NULL;

    Result result;

    if(isMale(parent))
    {
        result = assignFather(child, parent);

        if(result != SUCCESS)
            return result;

        if(hasSpouse(parent))
        {
            result = assignMother(
                        child,
                        parent->extendFamily.spouse
                     );

            if(result != SUCCESS)
                return result;
        }
    }
    else
    {
        result = assignMother(child, parent);

        if(result != SUCCESS)
            return result;

        if(hasSpouse(parent))
        {
            result = assignFather(
                        child,
                        parent->extendFamily.spouse
                     );

            if(result != SUCCESS)
                return result;
        }
    }

    return SUCCESS;
}


Result createChild(Person* parent)
{
    if(parent == nullptr)
        return PERSON_NULL;

    if(parent->status == DECEASED)
        return PERSON_DECEASED;

    cout << "\nEnter Child Name: ";

    string name = inputName();

    cout << "Enter Child Gender (male/female): ";

    string gender = inputGender();

    Person* child = createPerson(name, gender);

    Result result = validateChildRegistration(parent, child);

    if(result != SUCCESS)
    {
        destroyPerson(child);
        return result;
    }

    result = assignParents(child, parent);

    if(result != SUCCESS)
    {
        destroyPerson(child);
        return result;
    }

    result = addChildToParent(parent, child);

    if(result != SUCCESS)
    {
        destroyPerson(child);
        return result;
    }

    if(hasSpouse(parent))
    {
        result = addChildToParent(
                    parent->extendFamily.spouse,
                    child);

        if(result != SUCCESS)
        {
            return result;
        }
    }
    askOpenPersonMenu(child, parent);
    return SUCCESS;
}

Person* findPersonByIDRecursive(
            Person* current,
            int id,
            SearchNode*& visitedHead,
            SearchNode*& visitedTail)
{
    if(current == nullptr)
        return nullptr;

    if(current->visited)
        return nullptr;

    current->visited = true;

    addSearchResult(
        visitedHead,
        visitedTail,
        current
    );

    if(current->id == id)
        return current;

    Person* result =
        findPersonByIDRecursive(
            current->fromFamily.father,
            id,
            visitedHead,
            visitedTail);

    if(result != nullptr)
        return result;

    result =
        findPersonByIDRecursive(
            current->fromFamily.mother,
            id,
            visitedHead,
            visitedTail);

    if(result != nullptr)
        return result;

    result =
        findPersonByIDRecursive(
            current->extendFamily.spouse,
            id,
            visitedHead,
            visitedTail);

    if(result != nullptr)
        return result;

    Person* child =
        current->extendFamily.firstChild;

    while(child != nullptr)
    {
        result =
            findPersonByIDRecursive(
                child,
                id,
                visitedHead,
                visitedTail);

        if(result != nullptr)
            return result;

        child = child->rightSibling;
    }

    return nullptr;
}
Person* findPersonByID(int id)
{
    if(id <= 0)
        return nullptr;

    SearchNode* visitedHead = nullptr;
    SearchNode* visitedTail = nullptr;

    Person* found = nullptr;

    FamilyTree* currentTree = familyForestHead;

    while(currentTree != nullptr)
    {
        found =
            findPersonByIDRecursive(
                currentTree->root,
                id,
                visitedHead,
                visitedTail);

        if(found != nullptr)
            break;

        currentTree = currentTree->next;
    }

    SearchNode* visitedCurrent = visitedHead;

    while(visitedCurrent != nullptr)
    {
        visitedCurrent->person->visited = false;

        visitedCurrent = visitedCurrent->next;
    }

    destroySearchResults(visitedHead);

    return found;
}

void searchMenu()
{
    while(true)
    {
        cout << "\n=====================================\n";
        cout << "             SEARCH MENU\n";
        cout << "=====================================\n";

        cout << "1. Search By ID\n";
        cout << "2. Search By Name\n";
        cout << "3. Back\n";

        int choice =
            inputChoice(
                1,
                3,
                "\nEnter Choice: "
            );

        switch(choice)
        {
            case 1:

                searchByID();

                break;

            case 2:

                searchByName();

                break;

            case 3:

                return;
        }
    }
}

void searchByID()
{
    cout << "\nEnter Person ID: ";

    int id = inputInteger();

    Person* person = findPersonByID(id);

    if(person == nullptr)
    {
        cout << "\nPerson not found.\n";
        return;
    }

    cout << "\nPerson Found.\n";

    printPersonDetailed(person);

    askOpenPersonMenu(person);
}


void findPersonsByNameRecursive(
        Person* current,
        const string& name,
        SearchNode*& head,
        SearchNode*& tail,
        SearchNode*& visitedHead,
        SearchNode*& visitedTail)
{
    if(current == nullptr)
        return;

    if(current->visited)
        return;

    current->visited = true;

    addSearchResult(
        visitedHead,
        visitedTail,
        current
    );

    if(toLowerCase(current->name) == name)
    {
        addSearchResult(
            head,
            tail,
            current
        );
    }

    // Follow every relation, not just descendants, so people
    // who don't have their own tree (linked parents, spouses,
    // etc.) are still reachable from the search.

    findPersonsByNameRecursive(
        current->fromFamily.father,
        name,
        head,
        tail,
        visitedHead,
        visitedTail
    );

    findPersonsByNameRecursive(
        current->fromFamily.mother,
        name,
        head,
        tail,
        visitedHead,
        visitedTail
    );

    findPersonsByNameRecursive(
        current->extendFamily.spouse,
        name,
        head,
        tail,
        visitedHead,
        visitedTail
    );

    Person* child =
        current->extendFamily.firstChild;

    while(child != nullptr)
    {
        findPersonsByNameRecursive(
            child,
            name,
            head,
            tail,
            visitedHead,
            visitedTail
        );

        child = child->rightSibling;
    }
}


Person* findPersonsByName(
        const string& name)
{
    SearchNode* head = nullptr;
    SearchNode* tail = nullptr;

    SearchNode* visitedHead = nullptr;
    SearchNode* visitedTail = nullptr;

    string searchName = toLowerCase(name);

    FamilyTree* tree = familyForestHead;

    while(tree != nullptr)
    {
        findPersonsByNameRecursive(
            tree->root,
            searchName,
            head,
            tail,
            visitedHead,
            visitedTail
        );

        tree = tree->next;
    }

    SearchNode* visitedCurrent = visitedHead;

    while(visitedCurrent != nullptr)
    {
        visitedCurrent->person->visited = false;

        visitedCurrent = visitedCurrent->next;
    }

    destroySearchResults(visitedHead);

    if(head == nullptr)
        return nullptr;

    cout << "\n=========== SEARCH RESULTS ===========\n";

    printSearchResults(head);

    Person* selected =
        chooseSearchResult(head);

    destroySearchResults(head);

    return selected;
}

void searchByName()
{
    cout << "\nEnter Person Name: ";

    string name = inputName();

    Person* selectedPerson =
        findPersonsByName(name);

    if(selectedPerson == nullptr)
    {
        cout << "\nNo person found.\n";
        return;
    }

    cout << "\nPerson Found.\n";

    printPersonDetailed(selectedPerson);

    askOpenPersonMenu(selectedPerson);
}

void printSearchResults(
        SearchNode* head)
{
    int index = 1;

    while(head != nullptr)
    {
        cout << index
             << ". "
             << head->person->name
             << " (ID : "
             << head->person->id
             << ", "
             << getLifeStatusString(
                    head->person->status)
             << ")\n";

        index++;

        head = head->next;
    }
}

Person* chooseSearchResult(
        SearchNode* head)
{
    if(head == nullptr)
        return nullptr;

    int count = 0;

    SearchNode* current = head;

    while(current != nullptr)
    {
        count++;

        current = current->next;
    }

    cout << "\n0. Cancel\n";

    int choice =
        inputChoice(
            0,
            count,
            "\nSelect Person: "
        );

    if(choice == 0)
        return nullptr;

    current = head;

    for(int i = 1; i < choice; i++)
    {
        current = current->next;
    }

    return current->person;
}


Person* findExistingPerson()
{
    while(true)
    {
        cout << "\n=====================================\n";
        cout << "      FIND EXISTING PERSON\n";
        cout << "=====================================\n";

        cout << "1. Search by ID\n";
        cout << "2. Search by Name\n";
        cout << "3. Cancel\n\n";

        int choice =
            inputChoice(
                1,
                3,
                "Enter Choice: "
            );

        switch(choice)
        {
            case 1:
            {
                cout << "\nEnter Person ID: ";

                int id = inputInteger();

                Person* person =
                    findPersonByID(id);

                if(person != nullptr)
                    return person;

                cout << "\nPerson not found.\n";
                break;
            }

            case 2:
            {
                cout << "\nEnter Person Name: ";

                string name =
                    inputName();

                Person* person =
                    findPersonsByName(name);

                if(person != nullptr)
                    return person;

                cout << "\nPerson not found.\n";
                break;
            }

            case 3:
                return nullptr;
        }
    }
}


Result createTreeForPerson(Person* root)
{
    Result result =
        validateTreeCreation(root);

    if(result != SUCCESS)
        return result;

    FamilyTree* tree =
        createFamilyTree(root);

    if(tree == nullptr)
        return UNKNOWN_ERROR;

    result = addTree(tree);

    return result;
}


void addSearchResult(
        SearchNode*& head,
        SearchNode*& tail,
        Person* person)
{
    SearchNode* existing = head;

    while(existing != nullptr)
    {
        if(existing->person->id == person->id)
            return;

        existing = existing->next;
    }

    SearchNode* node = new SearchNode;

    node->person = person;

    if(head == nullptr)
    {
        head = node;
        tail = node;
        return;
    }

    tail->next = node;

    tail = node;
}


void destroySearchResults(
        SearchNode*& head)
{
    while(head != nullptr)
    {
        SearchNode* temp = head;

        head = head->next;

        delete temp;
    }
}

Person* viewParents(Person* person)
{
    if(person == nullptr)
        return nullptr;
    Person* parents[2];

    int count = 0;

    cout << "\n=====================================\n";
    cout << "             PARENTS\n";
    cout << "=====================================\n";

    if(hasFather(person))
    {
        parents[count] = person->fromFamily.father;

        cout << count + 1
             << ". Father : "
             << parents[count]->name
             << " (ID : "
             << parents[count]->id
             << ", "
             << getLifeStatusString(parents[count]->status)
             << ")\n";
             count++;
    }

    if(hasMother(person))
    {
        parents[count] = person->fromFamily.mother;

        cout << count + 1
             << ". Mother : "
             << parents[count]->name
             << " (ID : "
             << parents[count]->id
             << ", "
             << getLifeStatusString(parents[count]->status)
             << ")\n";
        count++;
    }

    if(count == 0)
    {
        cout << "\nNo parents registered.\n";
        return nullptr;
    }

    cout << "\n0. Back\n";

    int choice =
        inputChoice(
            0,
            count,
            "\nSelect Parent: "
        );

    if(choice == 0)
        return nullptr;

    pushHistory(person);
    return parents[choice - 1];
}

Person* viewSpouse(Person* person)
{
    if(person == nullptr)
        return nullptr;

    cout << "\n=====================================\n";
    cout << "             SPOUSE\n";
    cout << "=====================================\n";

    if(!hasSpouse(person))
    {
        cout << "\nNo spouse registered.\n";
        return nullptr;
    }

    Person* spouse =
        person->extendFamily.spouse;

    cout << "\n1. "
         << spouse->name
         << " (ID : "
         << spouse->id
         << ", "
         << getLifeStatusString(spouse->status)
         << ")\n";

    cout << "\n0. Back\n";

    int choice =
        inputChoice(
            0,
            1,
            "\nSelect Option: "
        );

    if(choice == 0)
        return nullptr;

    pushHistory(person);

    return spouse;
}


Person* viewChildren(Person* person)
{
    if(person == nullptr)
        return nullptr;

    cout << "\n=====================================\n";
    cout << "             CHILDREN\n";
    cout << "=====================================\n";

    if(!hasChildren(person))
    {
        cout << "\nNo children registered.\n";
        return nullptr;
    }

    Person* children[100];

    int count = 0;

    Person* current =
        person->extendFamily.firstChild;

    while(current != nullptr)
    {
        children[count] = current;

        cout << count + 1
             << ". "
             << current->name
             << " (ID : "
             << current->id
             << ", "
             << getLifeStatusString(current->status)
             << ")\n";

        count++;

        current = current->rightSibling;
    }

    cout << "\n0. Back\n";

    int choice =
        inputChoice(
            0,
            count,
            "\nSelect Child: "
        );

    if(choice == 0)
        return nullptr;

    pushHistory(person);

    return children[choice - 1];
}


Person* viewSiblings(Person* person)
{
    if(person == nullptr)
        return nullptr;

    cout << "\n=====================================\n";
    cout << "             SIBLINGS\n";
    cout << "=====================================\n";

    Person* parent = nullptr;

    if(hasFather(person))
        parent = person->fromFamily.father;
    else if(hasMother(person))
        parent = person->fromFamily.mother;

    if(parent == nullptr)
    {
        cout << "\nNo sibling information available.\n";
        return nullptr;
    }

    Person* siblings[100];

    int count = 0;

    Person* current =
        parent->extendFamily.firstChild;

    while(current != nullptr)
    {
        if(current != person)
        {
            siblings[count] = current;

            cout << count + 1
                 << ". "
                 << current->name
                 << " (ID : "
                 << current->id
                 << ", "
                 << getLifeStatusString(current->status)
                 << ")\n";

            count++;
        }

        current = current->rightSibling;
    }

    if(count == 0)
    {
        cout << "\nNo siblings found.\n";
        return nullptr;
    }

    cout << "\n0. Back\n";

    int choice =
        inputChoice(
            0,
            count,
            "\nSelect Sibling: "
        );

    if(choice == 0)
        return nullptr;

    pushHistory(person);

    return siblings[choice - 1];
}

Result updatePersonName(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    cout << "\nCurrent Name : "
         << person->name
         << endl;

    cout << "\nEnter New Name: ";

    string newName = inputName();

    if(newName == person->name)
        return ALREADY_EXISTS;

    person->name = newName;

    return SUCCESS;
}

Result updateLifeStatus(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    cout << "\nCurrent Status : "
         << getLifeStatusString(person->status)
         << endl;

    cout << "\n1. Alive\n";
    cout << "2. Deceased\n";
    cout << "3. Back\n";

    int choice =
        inputChoice(
            1,
            3,
            "\nEnter Choice: "
        );

    switch(choice)
    {
        case 1:

            if(person->status == ALIVE)
                return ALREADY_EXISTS;

            person->status = ALIVE;

            return SUCCESS;

        case 2:

            if(person->status == DECEASED)
                return ALREADY_EXISTS;

            person->status = DECEASED;
            if(hasSpouse(person))
                disconnectSpouses(person);

            return SUCCESS;

        case 3:

            return OPERATION_CANCELLED;
    }

    return UNKNOWN_ERROR;
}

Result divorcePerson(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    if(!hasSpouse(person))
        return PERSON_NOT_FOUND;

    Person* spouse =
        person->extendFamily.spouse;

    cout << "\n"
         << person->name
         << " is currently married to "
         << spouse->name
         << ".\n";

    cout << "\n1. Confirm Divorce\n";
    cout << "2. Cancel\n";

    int choice =
        inputChoice(
            1,
            2,
            "\nEnter Choice: "
        );

    if(choice == 2)
        return OPERATION_CANCELLED;

    return disconnectSpouses(person);
}

void updatePersonMenu(Person* person)
{
    if(person == nullptr)
        return;

    while(true)
    {
        cout << "\n=====================================\n";
        cout << "         UPDATE PERSON\n";
        cout << "=====================================\n";

        cout << "1. Change Name\n";
        cout << "2. Change Life Status\n";
        cout << "3. End Marriage (Divorce)\n";
        cout << "4. Back\n";

        int choice =
            inputChoice(
                1,
                4,
                "\nEnter Choice: "
            );

        Result result;

        switch(choice)
        {
            case 1:

                result =
                    updatePersonName(person);

                printResult(result);

                break;

            case 2:

                result =
                    updateLifeStatus(person);

                printResult(result);

                break;

            case 3:

                result =
                    divorcePerson(person);

                printResult(result);

                break;

            case 4:

                return;
        }
    }
}

void askOpenPersonMenu(Person* person, Person* cameFrom)
{
    if(person == nullptr)
        return;

    cout << "\n1. Open "
         << person->name
         << "'s Menu\n";

    cout << "2. Return to Main Menu\n\n";

    int choice =
        inputChoice(
            1,
            2,
            "Enter Choice: "
        );

    if(choice == 1)
    {
        if(cameFrom != nullptr)
            pushHistory(cameFrom);
        else
            clearHistory();

        personMenu(person);
    }
}


Result renamePerson(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    cout << "\nCurrent Name : "
         << person->name
         << endl;

    cout << "\nEnter New Name: ";

    string newName =
        inputName();

    if(newName == person->name)
    {
        cout << "\nNew name is the same as current name.\n";
        return OPERATION_CANCELLED;
    }

    person->name = newName;

    cout << "\nPerson renamed successfully.\n";

    return SUCCESS;
}

Result markPersonDeceased(Person* person)
{
    if(person == nullptr)
        return PERSON_NULL;

    if(person->status == DECEASED)
        return PERSON_DECEASED;

    cout << "\nMark "
         << person->name
         << " as deceased?\n\n";

    cout << "1. Yes\n";
    cout << "2. No\n\n";

    int choice =
        inputChoice(
            1,
            2,
            "Enter Choice: "
        );

    if(choice == 2)
        return OPERATION_CANCELLED;

    person->status = DECEASED;

    cout << "\nPerson marked as deceased.\n";

    return SUCCESS;
}


void personMenu(Person*& currentPerson)
{
    if(currentPerson == nullptr)
        return;

    while(true)
    {
        cout << "\n=====================================\n";
        cout << "           PERSON MENU\n";
        cout << "=====================================\n";

        printPersonDetailed(currentPerson);

        cout << "\n1. View Parents\n";
        cout << "2. View Children\n";
        cout << "3. View Siblings\n";
        cout << "4. View Spouse\n";
        cout << "5. Register Relationships\n";
        cout << "6. Update Person\n";
        cout << "7. Previous Person\n";
        cout << "8. Back\n";

        int choice =
            inputChoice(
                1,
                8,
                "\nEnter Choice: "
            );

        switch(choice)
        {
            case 1:
            {
                Person* selected =
                    viewParents(currentPerson);

                if(selected != nullptr)
                    currentPerson = selected;

                break;
            }

            case 2:
            {
                Person* selected =
                    viewChildren(currentPerson);

                if(selected != nullptr)
                    currentPerson = selected;

                break;
            }

            case 3:
            {
                Person* selected =
                    viewSiblings(currentPerson);

                if(selected != nullptr)
                    currentPerson = selected;

                break;
            }

            case 4:
            {
                Person* selected =
                    viewSpouse(currentPerson);

                if(selected != nullptr)
                    currentPerson = selected;

                break;
            }

            case 5:

                registerRelationshipMenu(currentPerson);

                break;

            case 6:

                updatePersonMenu(currentPerson);

                break;

            case 7:

            {
                Person* previous =
                    popHistory();

                if(previous == nullptr)
                {
                    cout << "\nNo previous person available.\n";
                }
                else
                {
                    currentPerson = previous;
                }

                break;
            }

            case 8:

                return;
        }
    }
}

void printFamilyTree(Person* root)
{
    if(root == nullptr)
        return;

    cout << "\n=====================================\n";
    cout << "          FAMILY TREE\n";
    cout << "=====================================\n\n";

    cout
        << root->name
        << " (ID: "
        << root->id
        << ", "
        << getLifeStatusString(root->status)
        << ")"
        << endl;

    if(hasSpouse(root))
    {
        cout
            << "Spouse: "
            << root->extendFamily.spouse->name
            << " ("
            << getLifeStatusString(
                root->extendFamily.spouse->status)
            << ")\n";
    }

    Person* child = root->extendFamily.firstChild;

    while(child != nullptr)
    {
        bool lastChild =
            (child->rightSibling == nullptr);

        printPersonRecursive(
            child,
            "",
            lastChild);

        child = child->rightSibling;
    }
}


void printPersonRecursive(
        Person* person,
        string prefix,
        bool isLast)
{
    if(person == nullptr)
        return;

    // Print current person
    cout << prefix;

    if(isLast)
        cout << "└── ";
    else
        cout << "├── ";

    cout << person->name
         << " (ID: "
         << person->id
         << ", "
         << getLifeStatusString(person->status)
         << ")"
         << endl;

    // Print spouse (if any)
    if(hasSpouse(person))
    {
        cout << prefix;

        if(isLast)
            cout << "    ";
        else
            cout << "│   ";

        cout << "Spouse: "
             << person->extendFamily.spouse->name
             << " (ID: "
             << person->extendFamily.spouse->id
             << ", "
             << getLifeStatusString(
                    person->extendFamily.spouse->status)
             << ")"
             << endl;
    }

    // Prepare indentation for children
    string childPrefix = prefix;

    if(isLast)
        childPrefix += "    ";
    else
        childPrefix += "│   ";

    // Print all children recursively
    Person* child = person->extendFamily.firstChild;

    while(child != nullptr)
    {
        bool lastChild =
            (child->rightSibling == nullptr);

        printPersonRecursive(
            child,
            childPrefix,
            lastChild);

        child = child->rightSibling;
    }
}

void viewFamilyTree()
{
    if(familyForestHead == nullptr)
    {
        cout << "\nNo Family Trees Available.\n";
        return;
    }

    cout << "\n=====================================\n";
    cout << "          FAMILY TREES\n";
    cout << "=====================================\n";

    printAllTrees();

    cout << "\nEnter Tree ID: ";

    int treeID = inputInteger();

    FamilyTree* tree =
        findTreeByID(treeID);

    if(tree == nullptr)
    {
        cout << "\nInvalid Tree ID.\n";
        return;
    }

    printFamilyTree(tree->root);
}

string escapeXML(string text)
{
    string escaped = "";

    for(char ch : text)
    {
        switch(ch)
        {
            case '&':
                escaped += "&amp;";
                break;

            case '<':
                escaped += "&lt;";
                break;

            case '>':
                escaped += "&gt;";
                break;

            case '\"':
                escaped += "&quot;";
                break;

            case '\'':
                escaped += "&apos;";
                break;

            default:
                escaped += ch;
        }
    }

    return escaped;
}

void createXML()
{
    if(familyForestHead == nullptr)
    {
        cout << "\nNo Family Trees Available.\n";
        return;
    }

    ofstream file("FamilyForest.xml");

    if(!file)
    {
        cout << "\nUnable to create XML file.\n";
        return;
    }

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";

    file << "<FamilyForest>\n\n";

    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        file << "    <FamilyTree id=\""
             << current->treeID
             << "\">\n\n";

        writeXML(
            current->root,
            file,
            8
        );

        file << "    </FamilyTree>\n\n";

        current = current->next;
    }

    file << "</FamilyForest>\n";

    file.close();

    cout << "\nFamily Forest exported successfully.\n";
}

void writeXML(Person* person,
              ofstream& file,
              int indentation)
{
    if(person == nullptr)
        return;

    writeIndentation(file, indentation);
    file << "<Person id=\""
         << person->id
         << "\">\n";

    // Name
    writeIndentation(file, indentation + 4);
    file << "<Name>"
         << escapeXML(person->name)
         << "</Name>\n";

    // Gender
    writeIndentation(file, indentation + 4);
    file << "<Gender>"
         << person->gender
         << "</Gender>\n";

    // Status
    writeIndentation(file, indentation + 4);
    file << "<Status>"
         << getLifeStatusString(person->status)
         << "</Status>\n";

    // Father
    writeIndentation(file, indentation + 4);
    file << "<FatherID>";

    if(hasFather(person))
        file << person->fromFamily.father->id;

    file << "</FatherID>\n";

    // Mother
    writeIndentation(file, indentation + 4);
    file << "<MotherID>";

    if(hasMother(person))
        file << person->fromFamily.mother->id;

    file << "</MotherID>\n";

    // Spouse
    writeIndentation(file, indentation + 4);
    file << "<SpouseID>";

    if(hasSpouse(person))
        file << person->extendFamily.spouse->id;

    file << "</SpouseID>\n";

    // Children
    writeIndentation(file, indentation + 4);
    file << "<Children>\n";

    Person* child = person->extendFamily.firstChild;

    while(child != nullptr)
    {
        writeXML(
            child,
            file,
            indentation + 8
        );

        child = child->rightSibling;
    }

    writeIndentation(file, indentation + 4);
    file << "</Children>\n";

    writeIndentation(file, indentation);
    file << "</Person>\n";
}


Result removeTreeFromForest(FamilyTree* tree)
{
    if(tree == nullptr)
        return PERSON_NULL;

    // Tree is first node
    if(familyForestHead == tree)
    {
        familyForestHead = tree->next;

        tree->next = nullptr;

        return SUCCESS;
    }

    FamilyTree* previous = familyForestHead;

    while(previous != nullptr &&
          previous->next != tree)
    {
        previous = previous->next;
    }

    if(previous == nullptr)
        return PERSON_NOT_FOUND;

    previous->next = tree->next;

    tree->next = nullptr;

    return SUCCESS;
}

void freePerson(Person* person)
{
    if(person == nullptr)
        return;

    Person* child =
        person->extendFamily.firstChild;

    while(child != nullptr)
    {
        Person* nextChild =
            child->rightSibling;

        freePerson(child);

        child = nextChild;
    }

    delete person;
}

void deleteFamilyTree(FamilyTree* tree)
{
    if(tree == nullptr)
    {
        cout << "\nFamily Tree not found.\n";
        return;
    }

    Result result =
        removeTreeFromForest(tree);

    if(result != SUCCESS)
    {
        printResult(result);
        return;
    }

    freePerson(tree->root);

    tree->root = nullptr;

    delete tree;

    cout << "\nFamily Tree deleted successfully.\n";
}

void deleteTreeMenu()
{
    if(familyForestHead == nullptr)
    {
        cout << "\nNo Family Trees Available.\n";
        return;
    }

    printAllTrees();

    cout << "\nEnter Tree ID to delete: ";

    int treeID = inputInteger();

    FamilyTree* tree =
        findTreeByID(treeID);

    if(tree == nullptr)
    {
        cout << "\nFamily Tree not found.\n";
        return;
    }

    cout << "\nYou are about to delete:\n";

    cout << "Tree ID : "
         << tree->treeID
         << endl;

    cout << "Root : "
         << tree->root->name
         << endl;

    cout << "\nThis operation cannot be undone.\n";

    cout << "\nDelete this Family Tree?\n";

    char choice =
        inputYesNo();

    if(choice == 'n')
    {
        cout << "\nOperation cancelled.\n";
        return;
    }

    deleteFamilyTree(tree);
}

void freeAllTrees()
{
    FamilyTree* current = familyForestHead;

    while(current != nullptr)
    {
        FamilyTree* nextTree =
            current->next;

        freePerson(current->root);

        current->root = nullptr;
        current->next = nullptr;

        delete current;

        current = nextTree;
    }

    familyForestHead = nullptr;
}

void pushHistory(Person* person)
{
    if(person == nullptr)
        return;

    HistoryNode* newNode = new HistoryNode;

    newNode->currentPerson = person;

    newNode->next = historyTop;

    historyTop = newNode;
}

Person* popHistory()
{
    if(historyTop == nullptr)
        return nullptr;

    HistoryNode* temp = historyTop;

    Person* person = temp->currentPerson;

    historyTop = historyTop->next;

    delete temp;

    return person;
}

Person* peekHistory()
{
    if(historyTop == nullptr)
        return nullptr;

    return historyTop->currentPerson;
}

bool isHistoryEmpty()
{
    return historyTop == nullptr;
}

void clearHistory()
{
    while(historyTop != nullptr)
    {
        HistoryNode* temp = historyTop;

        historyTop = historyTop->next;

        delete temp;
    }
}

void displayMainMenu()
{
    cout << "\n=============================================\n";
    cout << "      FAMILY TREE MANAGEMENT SYSTEM\n";
    cout << "=============================================\n";

    cout << "1. Register New Family Tree\n";
    cout << "2. Search Person\n";
    cout << "3. View Family Tree\n";
    cout << "4. Export XML\n";
    cout << "5. Delete Family Tree\n";
    cout << "0. Exit\n";

    cout << "=============================================\n";
}