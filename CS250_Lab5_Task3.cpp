#include <iostream>
#include <string>

using namespace std;

// Node representing one train coach
struct Coach
{
    int coachNumber;
    string coachType;
    int passengerCapacity;
    int currentPassengers;

    Coach* next;
    Coach* prev;
};


// Circular Doubly Linked List for Train
class Train
{
private:
    Coach* current;

    // Display information of one coach
    void displayCoach(Coach* coach)
    {
        cout << "Coach Number: " << coach->coachNumber << endl;
        cout << "Coach Type: " << coach->coachType << endl;
        cout << "Passenger Capacity: "
             << coach->passengerCapacity << endl;
        cout << "Current Passengers: "
             << coach->currentPassengers << endl;
        cout << "Available Capacity: "
             << coach->passengerCapacity - coach->currentPassengers
             << endl;

        cout << "-----------------------------" << endl;
    }

public:

    // Constructor
    Train()
    {
        current = nullptr;
    }


    // Destructor
    ~Train()
    {
        if (current == nullptr)
        {
            return;
        }

        Coach* temp = current->next;

        while (temp != current)
        {
            Coach* nextCoach = temp->next;

            delete temp;

            temp = nextCoach;
        }

        delete current;

        current = nullptr;
    }


    // 1. Add coach at the end
    void addCoach(
        int number,
        string type,
        int capacity,
        int passengers)
    {
        Coach* newCoach = new Coach;

        newCoach->coachNumber = number;
        newCoach->coachType = type;
        newCoach->passengerCapacity = capacity;
        newCoach->currentPassengers = passengers;

        // If train is empty
        if (current == nullptr)
        {
            newCoach->next = newCoach;
            newCoach->prev = newCoach;

            current = newCoach;

            cout << "Coach added successfully." << endl;

            return;
        }

        // Last coach is current->prev
        Coach* last = current->prev;

        newCoach->next = current;
        newCoach->prev = last;

        last->next = newCoach;
        current->prev = newCoach;

        cout << "Coach added successfully." << endl;
    }


    // 2. Insert coach after specified coach number
    void insertCoach(
        int number,
        string type,
        int capacity,
        int passengers,
        int afterNumber)
    {
        if (current == nullptr)
        {
            cout << "Train is empty. "
                 << "There is no coach to insert after."
                 << endl;

            return;
        }

        Coach* temp = current;

        do
        {
            if (temp->coachNumber == afterNumber)
            {
                Coach* newCoach = new Coach;

                newCoach->coachNumber = number;
                newCoach->coachType = type;
                newCoach->passengerCapacity = capacity;
                newCoach->currentPassengers = passengers;

                Coach* nextCoach = temp->next;

                newCoach->prev = temp;
                newCoach->next = nextCoach;

                temp->next = newCoach;
                nextCoach->prev = newCoach;

                cout << "Coach inserted successfully."
                     << endl;

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number "
             << afterNumber
             << " not found."
             << endl;
    }


    // 3. Remove coach by coach number
    void removeCoach(int number)
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        Coach* temp = current;

        do
        {
            if (temp->coachNumber == number)
            {
                // Only one coach
                if (temp->next == temp)
                {
                    delete temp;

                    current = nullptr;

                    cout << "Coach removed successfully."
                         << endl;

                    return;
                }

                Coach* previousCoach = temp->prev;
                Coach* nextCoach = temp->next;

                previousCoach->next = nextCoach;
                nextCoach->prev = previousCoach;

                // If removing current,
                // next coach becomes current
                if (temp == current)
                {
                    current = nextCoach;
                }

                delete temp;

                cout << "Coach removed successfully."
                     << endl;

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number "
             << number
             << " not found."
             << endl;
    }


    // 4. Move forward
    void moveForward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        current = current->next;

        cout << "Moved forward." << endl;

        displayCoach(current);
    }


    // 5. Move backward
    void moveBackward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        current = current->prev;

        cout << "Moved backward." << endl;

        displayCoach(current);
    }


    // 6. Display train clockwise
    void displayClockwise()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        cout << "\n===== TRAIN CLOCKWISE ====="
             << endl;

        Coach* temp = current;

        do
        {
            displayCoach(temp);

            temp = temp->next;

        } while (temp != current);
    }


    // 7. Display train anti-clockwise
    void displayAntiClockwise()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        cout << "\n===== TRAIN ANTI-CLOCKWISE ====="
             << endl;

        Coach* temp = current;

        do
        {
            displayCoach(temp);

            temp = temp->prev;

        } while (temp != current);
    }


    // 8. Search coach
    void searchCoach(int number)
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        Coach* temp = current;

        do
        {
            if (temp->coachNumber == number)
            {
                cout << "\nCoach found!" << endl;

                displayCoach(temp);

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number "
             << number
             << " not found."
             << endl;
    }


    // 9. Find maximum available capacity
    void findMaximumAvailableCapacity()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        Coach* temp = current;

        Coach* maximumCoach = current;

        int maximumAvailable =
            current->passengerCapacity -
            current->currentPassengers;

        temp = temp->next;

        while (temp != current)
        {
            int available =
                temp->passengerCapacity -
                temp->currentPassengers;

            if (available > maximumAvailable)
            {
                maximumAvailable = available;

                maximumCoach = temp;
            }

            temp = temp->next;
        }

        cout << "\n===== MAXIMUM AVAILABLE CAPACITY ====="
             << endl;

        cout << "Coach Number: "
             << maximumCoach->coachNumber
             << endl;

        cout << "Coach Type: "
             << maximumCoach->coachType
             << endl;

        cout << "Available Capacity: "
             << maximumAvailable
             << endl;
    }


    // 10. Display current coach
    void displayCurrentCoach()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        cout << "\n===== CURRENT COACH ====="
             << endl;

        displayCoach(current);
    }


    // 11. Reverse the whole train
    void reverseTrain()
    {
        if (current == nullptr)
        {
            cout << "Train is empty." << endl;

            return;
        }

        // Only one coach
        if (current->next == current)
        {
            cout << "Train reversed successfully."
                 << endl;

            return;
        }

        Coach* temp = current;

        do
        {
            // Save old next pointer
            Coach* oldNext = temp->next;

            // Swap next and previous pointers
            temp->next = temp->prev;
            temp->prev = oldNext;

            // Move using old next
            temp = oldNext;

        } while (temp != current);

        cout << "Train reversed successfully."
             << endl;
    }
};


// Main function
int main()
{
    Train train;

    int numberOfCoaches;

    cout << "Enter number of initial coaches: ";
    cin >> numberOfCoaches;


    // Enter initial coaches
    for (int i = 0; i < numberOfCoaches; i++)
    {
        int number;
        string type;
        int capacity;
        int passengers;

        cout << "\nEnter details for Coach "
             << i + 1 << endl;

        cout << "Coach Number: ";
        cin >> number;

        cout << "Coach Type: ";
        cin >> type;

        cout << "Passenger Capacity: ";
        cin >> capacity;

        cout << "Current Passengers: ";
        cin >> passengers;

        train.addCoach(
            number,
            type,
            capacity,
            passengers
        );
    }


    int choice;

    do
    {
        cout << "\n========== TRAIN MENU =========="
             << endl;

        cout << "1. Add Coach at End" << endl;
        cout << "2. Insert Coach After Coach Number" << endl;
        cout << "3. Remove Coach" << endl;
        cout << "4. Move Forward" << endl;
        cout << "5. Move Backward" << endl;
        cout << "6. Display Train Clockwise" << endl;
        cout << "7. Display Train Anti-clockwise" << endl;
        cout << "8. Search Coach" << endl;
        cout << "9. Find Maximum Available Capacity" << endl;
        cout << "10. Display Current Coach" << endl;
        cout << "11. Reverse Train Direction" << endl;
        cout << "12. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;


        // Add coach
        if (choice == 1)
        {
            int number;
            string type;
            int capacity;
            int passengers;

            cout << "Enter Coach Number: ";
            cin >> number;

            cout << "Enter Coach Type: ";
            cin >> type;

            cout << "Enter Passenger Capacity: ";
            cin >> capacity;

            cout << "Enter Current Passengers: ";
            cin >> passengers;

            train.addCoach(
                number,
                type,
                capacity,
                passengers
            );
        }


        // Insert coach after another coach
        else if (choice == 2)
        {
            int number;
            string type;
            int capacity;
            int passengers;
            int afterNumber;

            cout << "Enter new Coach Number: ";
            cin >> number;

            cout << "Enter Coach Type: ";
            cin >> type;

            cout << "Enter Passenger Capacity: ";
            cin >> capacity;

            cout << "Enter Current Passengers: ";
            cin >> passengers;

            cout << "Insert after Coach Number: ";
            cin >> afterNumber;

            train.insertCoach(
                number,
                type,
                capacity,
                passengers,
                afterNumber
            );
        }


        // Remove coach
        else if (choice == 3)
        {
            int number;

            cout << "Enter Coach Number to remove: ";
            cin >> number;

            train.removeCoach(number);
        }


        // Move forward
        else if (choice == 4)
        {
            train.moveForward();
        }


        // Move backward
        else if (choice == 5)
        {
            train.moveBackward();
        }


        // Display clockwise
        else if (choice == 6)
        {
            train.displayClockwise();
        }


        // Display anti-clockwise
        else if (choice == 7)
        {
            train.displayAntiClockwise();
        }


        // Search coach
        else if (choice == 8)
        {
            int number;

            cout << "Enter Coach Number to search: ";
            cin >> number;

            train.searchCoach(number);
        }


        // Maximum available capacity
        else if (choice == 9)
        {
            train.findMaximumAvailableCapacity();
        }


        // Current coach
        else if (choice == 10)
        {
            train.displayCurrentCoach();
        }


        // Reverse train
        else if (choice == 11)
        {
            train.reverseTrain();
        }


        // Exit
        else if (choice == 12)
        {
            cout << "Exiting program..."
                 << endl;
        }


        else
        {
            cout << "Invalid choice."
                 << endl;
        }

    } while (choice != 12);


    return 0;
}
