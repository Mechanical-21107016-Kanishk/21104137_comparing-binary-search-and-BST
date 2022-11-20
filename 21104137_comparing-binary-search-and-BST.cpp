#include <iostream>
#include <vector>
using namespace std;

class BST {
    int data;
    BST *left, *right;
 
public:
    // default constructor
    BST ()
        : data(0), left(NULL), right(NULL) {}
 
    // parameterized constructor
    BST (int value) {
        data = value;
        left = right = NULL;
    }
 
    // function to insert nodes in BST
    BST* insert(BST* root, int value) {
        if (!root) 
            return new BST(value);
    
        if (value > root->data) {
            root->right = insert(root->right, value);
        }
        else if (value < root->data){
            root->left = insert(root->left, value);
        }
    
        return root;
    }

    void insertNode(BST b, BST** root, int value) {
        if (*root == nullptr)
            *root = b.insert(*root, value);
        else
            b.insert(*root, value);
    }
 
    // function to print the nodes in order
    void print(BST* root) {
        if (!root)
            return;
        print(root->left);
        cout << root->data << "   ";
        print(root->right);
    }

    // funtion to find min value node
    BST* minValueNode(BST* node) {
        BST* current = node;
    
        /* loop down to find the leftmost leaf */
        while (current && current->left != NULL)
            current = current->left;
    
        return current;
    }

    // function to delete a node
    BST* deleteNode(BST* root, int key) {
        if (!root)
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            // node has no child
            if (root->left==NULL and root->right==NULL)
                return NULL;
            
            // node with only one child or no child
            else if (root->left == NULL) {
                BST* temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL) {
                BST* temp = root->left;
                free(root);
                return temp;
            }
    
            BST* temp = minValueNode(root->right);
    
            // Copy the inorder successor's content to this node
            root->data = temp->data;
    
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }

        return root;
    }
};

// function to print array
void printArr(vector<int> arr) {
    cout << "Array: ";
    for (int element : arr) {
        cout << element << "   ";
    }
    cout << endl;
}

// quickSort function
int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high]; // assign last element as pivot
    int i = low - 1; // pointer to point at sorted division

    for (int j{low}; j < high; j++) {
        if (vec[j] < pivot) {
            i++; // whenever we encounter an element smaller than pivot, i increments
            swap(vec[j], vec[i]); // swap with the leftmost bigger element
        }
    }
    swap(vec[i + 1], vec[high]); // swapping pivot with leftmost bigger element
    return i + 1; // current position of pivot
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

// binary search on a sorted list and delete the element
void deleteArrElement(vector<int> &arr, int low, int high, int key) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
 
        if (arr[mid] == key){
            arr.erase(arr.begin() + mid);
            return;
        }
        if (arr[mid] > key)
            deleteArrElement(arr, low, mid - 1, key);
        deleteArrElement(arr, mid + 1, high, key);
    }
}

int main () {
    // 1. array of numbers
    vector<int> arr{50, 30, 40, 10, 90, 70, 60, 20};
    printArr(arr);
    
    BST b, *root = NULL;

    // 2. constructing a BST
    for (int element : arr) {
        b.insertNode(b, &root, element);
    }
    
    cout << "BST: ";
    b.print(root);
    
    // 3. deleting a BST node
    cout << "\n\nDeleting Node with data 30" << endl;
    root = b.deleteNode(root, 30);
    cout << "BST: ";
    b.print(root);

    // deleting an array element
    cout << "\n\nDeleting an element with data 30" << endl;
    quickSort(arr, 0, arr.size() - 1); // sorting the array before calling quickSort
    deleteArrElement(arr, 0, arr.size() - 1, 30);
    printArr(arr);

/*  The space complexity of quicksort is O(n*logn)
    The space complexity of binary search is O(1) 
    So total space complexity for deletion using function deleteArrElement is O(n*logn) + O(1) 
    
    The space complexity of binary search tree is O(1) 
    So total space complexity for deletion using function deleteNode is O(1) 

    => Binary search tree is better in terms of space complexity
*/
}