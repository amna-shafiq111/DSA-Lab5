#include <iostream>
#include <string>

using namespace std;

// Node for each photo
struct Photo
{
    int photoID;
    string photoName;
    string dateTaken;
    string location;

    Photo* next;
    Photo* prev;
};

// Circular Doubly Linked List for Photo Album
class PhotoAlbum
{
private:
    Photo* current;

    // Display one photo
    void displayPhoto(Photo* photo)
    {
        cout << "Photo ID: " << photo->photoID << endl;
        cout << "Photo Name: " << photo->photoName << endl;
        cout << "Date Taken: " << photo->dateTaken << endl;
        cout << "Location: " << photo->location << endl;
        cout << "-----------------------------" << endl;
    }

public:

    // Constructor
    PhotoAlbum()
    {
        current = nullptr;
    }

    // Destructor
    ~PhotoAlbum()
    {
        if (current == nullptr)
        {
            return;
        }

        Photo* temp = current->next;

        while (temp != current)
        {
            Photo* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete current;
        current = nullptr;
    }

    // 1. Add photo at the end
    void addPhoto(int id, string name, string date, string place)
    {
        Photo* newPhoto = new Photo;

        newPhoto->photoID = id;
        newPhoto->photoName = name;
        newPhoto->dateTaken = date;
        newPhoto->location = place;

        // If album is empty
        if (current == nullptr)
        {
            newPhoto->next = newPhoto;
            newPhoto->prev = newPhoto;

            current = newPhoto;

            cout << "Photo added successfully." << endl;
            return;
        }

        // Last photo is current->prev
        Photo* last = current->prev;

        newPhoto->next = current;
        newPhoto->prev = last;

        last->next = newPhoto;
        current->prev = newPhoto;

        cout << "Photo added successfully." << endl;
    }

    // 2. Insert photo after current
    void insertAfterCurrent(int id, string name, string date, string place)
    {
        if (current == nullptr)
        {
            cout << "Album is empty. Photo cannot be inserted after current." << endl;
            return;
        }

        Photo* newPhoto = new Photo;

        newPhoto->photoID = id;
        newPhoto->photoName = name;
        newPhoto->dateTaken = date;
        newPhoto->location = place;

        Photo* nextPhoto = current->next;

        newPhoto->prev = current;
        newPhoto->next = nextPhoto;

        current->next = newPhoto;
        nextPhoto->prev = newPhoto;

        cout << "Photo inserted after current photo." << endl;
    }

    // 3. Remove photo by ID
    void removePhoto(int id)
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        Photo* temp = current;

        do
        {
            if (temp->photoID == id)
            {
                // Only one photo
                if (temp->next == temp)
                {
                    delete temp;
                    current = nullptr;

                    cout << "Photo removed successfully." << endl;
                    return;
                }

                // If removing current photo
                if (temp == current)
                {
                    Photo* nextPhoto = temp->next;
                    Photo* previousPhoto = temp->prev;

                    previousPhoto->next = nextPhoto;
                    nextPhoto->prev = previousPhoto;

                    current = nextPhoto;

                    delete temp;

                    cout << "Photo removed successfully." << endl;
                    return;
                }

                // Removing some other photo
                Photo* previousPhoto = temp->prev;
                Photo* nextPhoto = temp->next;

                previousPhoto->next = nextPhoto;
                nextPhoto->prev = previousPhoto;

                delete temp;

                cout << "Photo removed successfully." << endl;
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Photo with ID " << id << " not found." << endl;
    }

    // 4. Remove current photo
    void removeCurrentPhoto()
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        // Only one photo
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "Current photo removed." << endl;
            return;
        }

        Photo* oldCurrent = current;
        Photo* nextPhoto = current->next;
        Photo* previousPhoto = current->prev;

        previousPhoto->next = nextPhoto;
        nextPhoto->prev = previousPhoto;

        current = nextPhoto;

        delete oldCurrent;

        cout << "Current photo removed." << endl;
    }

    // 5. Move to next photo
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        current = current->next;

        cout << "Moved to next photo." << endl;
        displayPhoto(current);
    }

    // 6. Move to previous photo
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        current = current->prev;

        cout << "Moved to previous photo." << endl;
        displayPhoto(current);
    }

    // 7. Display album forward
    void displayForward()
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        cout << "\n===== ALBUM FORWARD =====" << endl;

        Photo* temp = current;

        do
        {
            displayPhoto(temp);
            temp = temp->next;

        } while (temp != current);
    }

    // 8. Display album backward
    void displayBackward()
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        cout << "\n===== ALBUM BACKWARD =====" << endl;

        Photo* temp = current;

        do
        {
            displayPhoto(temp);
            temp = temp->prev;

        } while (temp != current);
    }

    // 9. Search photo by ID
    void searchPhoto(int id)
    {
        if (current == nullptr)
        {
            cout << "Album is empty." << endl;
            return;
        }

        Photo* temp = current;

        do
        {
            if (temp->photoID == id)
            {
                cout << "\nPhoto found!" << endl;
                displayPhoto(temp);
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Photo with ID " << id << " not found." << endl;
    }

    // 10. Count photos
    int countPhotos()
    {
        if (current == nullptr)
        {
            return 0;
        }

        int count = 0;
        Photo* temp = current;

        do
        {
            count++;
            temp = temp->next;

        } while (temp != current);

        return count;
    }
};


// Main function
int main()
{
    PhotoAlbum album;

    int numberOfPhotos;

    cout << "Enter number of initial photos: ";
    cin >> numberOfPhotos;

    for (int i = 0; i < numberOfPhotos; i++)
    {
        int id;
        string name;
        string date;
        string location;

        cout << "\nEnter details for Photo " << i + 1 << endl;

        cout << "Photo ID: ";
        cin >> id;

        cout << "Photo Name: ";
        cin >> name;

        cout << "Date Taken: ";
        cin >> date;

        cout << "Location: ";
        cin >> location;

        album.addPhoto(id, name, date, location);
    }

    int choice;

    do
    {
        cout << "\n========== PHOTO ALBUM MENU ==========" << endl;
        cout << "1. Add Photo at End" << endl;
        cout << "2. Insert Photo After Current" << endl;
        cout << "3. Remove Photo by ID" << endl;
        cout << "4. Remove Current Photo" << endl;
        cout << "5. Move Next" << endl;
        cout << "6. Move Previous" << endl;
        cout << "7. Display Album Forward" << endl;
        cout << "8. Display Album Backward" << endl;
        cout << "9. Search Photo by ID" << endl;
        cout << "10. Count Photos" << endl;
        cout << "11. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            string name;
            string date;
            string location;

            cout << "Enter Photo ID: ";
            cin >> id;

            cout << "Enter Photo Name: ";
            cin >> name;

            cout << "Enter Date Taken: ";
            cin >> date;

            cout << "Enter Location: ";
            cin >> location;

            album.addPhoto(id, name, date, location);
        }

        else if (choice == 2)
        {
            int id;
            string name;
            string date;
            string location;

            cout << "Enter Photo ID: ";
            cin >> id;

            cout << "Enter Photo Name: ";
            cin >> name;

            cout << "Enter Date Taken: ";
            cin >> date;

            cout << "Enter Location: ";
            cin >> location;

            album.insertAfterCurrent(id, name, date, location);
        }

        else if (choice == 3)
        {
            int id;

            cout << "Enter Photo ID to remove: ";
            cin >> id;

            album.removePhoto(id);
        }

        else if (choice == 4)
        {
            album.removeCurrentPhoto();
        }

        else if (choice == 5)
        {
            album.moveNext();
        }

        else if (choice == 6)
        {
            album.movePrevious();
        }

        else if (choice == 7)
        {
            album.displayForward();
        }

        else if (choice == 8)
        {
            album.displayBackward();
        }

        else if (choice == 9)
        {
            int id;

            cout << "Enter Photo ID to search: ";
            cin >> id;

            album.searchPhoto(id);
        }

        else if (choice == 10)
        {
            cout << "Total number of photos: "
                 << album.countPhotos() << endl;
        }

        else if (choice == 11)
        {
            cout << "Exiting program..." << endl;
        }

        else
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 11);

    return 0;
}
