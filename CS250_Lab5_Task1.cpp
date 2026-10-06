#include <iostream>
#include <string>

using namespace std;

// Node for each browser tab
struct Tab
{
    int tabID;
    string title;
    string url;

    Tab* next;
    Tab* prev;
};

// Browser Tab Manager using Circular Doubly Linked List
class BrowserTabManager
{
private:
    Tab* current;

public:

    // Constructor
    BrowserTabManager()
    {
        current = nullptr;
    }

    // Destructor
    ~BrowserTabManager()
    {
        if (current == nullptr)
            return;

        Tab* temp = current->next;

        while (temp != current)
        {
            Tab* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete current;
        current = nullptr;
    }

    // 1. Open New Tab
    void openNewTab(int id, string title, string url)
    {
        Tab* newTab = new Tab;

        newTab->tabID = id;
        newTab->title = title;
        newTab->url = url;

        // If list is empty
        if (current == nullptr)
        {
            newTab->next = newTab;
            newTab->prev = newTab;

            current = newTab;

            cout << "New tab opened as the first tab.\n";
            return;
        }

        // Insert after current
        newTab->next = current->next;
        newTab->prev = current;

        current->next->prev = newTab;
        current->next = newTab;

        cout << "New tab opened successfully.\n";
    }

    // 2. Close Current Tab
    void closeCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        // Only one tab
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "Current tab closed. No tabs remain.\n";
            return;
        }

        Tab* oldCurrent = current;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        current = current->next;

        delete oldCurrent;

        cout << "Current tab closed.\n";
    }

    // 3. Move Next
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->next;

        cout << "Moved to next tab.\n";
    }

    // 4. Move Previous
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->prev;

        cout << "Moved to previous tab.\n";
    }

    // 5. Display Current Tab
    void displayCurrent()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n===== Current Tab =====\n";
        cout << "Tab ID: " << current->tabID << endl;
        cout << "Website Title: " << current->title << endl;
        cout << "URL: " << current->url << endl;
    }

    // 6. Display All Tabs Forward
    void displayForward()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n===== All Tabs Forward =====\n";

        Tab* temp = current;

        do
        {
            cout << "Tab ID: " << temp->tabID << endl;
            cout << "Website Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            cout << "--------------------------\n";

            temp = temp->next;

        } while (temp != current);
    }

    // 7. Display All Tabs Backward
    void displayBackward()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n===== All Tabs Backward =====\n";

        Tab* temp = current;

        do
        {
            cout << "Tab ID: " << temp->tabID << endl;
            cout << "Website Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            cout << "--------------------------\n";

            temp = temp->prev;

        } while (temp != current);
    }

    // 8. Search Tab
    void searchTab(int id)
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        Tab* temp = current;

        do
        {
            if (temp->tabID == id)
            {
                cout << "\n===== Tab Found =====\n";
                cout << "Tab ID: " << temp->tabID << endl;
                cout << "Website Title: " << temp->title << endl;
                cout << "URL: " << temp->url << endl;
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Tab with ID " << id << " not found.\n";
    }
};


int main()
{
    BrowserTabManager browser;

    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << "       BROWSER TAB MANAGER\n";
        cout << "=================================\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            int id;
            string title;
            string url;

            cout << "Enter Tab ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Website Title: ";
            getline(cin, title);

            cout << "Enter URL: ";
            getline(cin, url);

            browser.openNewTab(id, title, url);
        }

        else if (choice == 2)
        {
            browser.closeCurrentTab();
        }

        else if (choice == 3)
        {
            browser.moveNext();
        }

        else if (choice == 4)
        {
            browser.movePrevious();
        }

        else if (choice == 5)
        {
            browser.displayCurrent();
        }

        else if (choice == 6)
        {
            browser.displayForward();
        }

        else if (choice == 7)
        {
            browser.displayBackward();
        }

        else if (choice == 8)
        {
            int id;

            cout << "Enter Tab ID to search: ";
            cin >> id;

            browser.searchTab(id);
        }

        else if (choice == 9)
        {
            cout << "Program ended.\n";
        }

        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}