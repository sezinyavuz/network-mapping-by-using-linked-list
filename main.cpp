#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

typedef vector<string> arraystring;
vector<arraystring> data;

//struct of apartments
struct node{
    string name;
    int max_bandwith;
    struct node* next;
    struct fnode* fnext;

};

//structs of flats
struct fnode{
    string flat_id;
    int initial_bandwith;
    fnode* next;
    fnode* prev;
    int index;

};

//function of adding an apartment to an empty list
struct node* addToEmpty(struct node* last, string name, int max_bandwith)
{

    if (last != 0)
        return last;


    struct node* temp = new node;

    temp->name = name;
    temp->max_bandwith = max_bandwith;
    last = temp;

    temp->next = last;

    return last;
}

//function of adding an apartment after to a certain apartment
struct node* addAfter(struct node* last, string name,int max_bandwith, string itemName)
{
    if (last == 0)
        return 0;

    struct node *temp, *p;
    p = last->next;

    do {
        if (p->name == itemName) {
            temp = new node;

            temp->name = name;
            temp->max_bandwith= max_bandwith;

            temp->next = p->next;

            p->next = temp;

            if (p == last)
                last = temp;

            return last;
        }
        p = p->next;
    } while (p != last->next);


    return last;
}


//function of adding an apartment before to a certain apartment
struct node* addBefore(struct node* last, string name,int max_bandwith, string itemName)
{
    if (last == 0)
        return 0;

    struct node *temp, *p;
    p = last->next;
    do {

        if ((p->next)->name == itemName) {
            temp = new node;

            temp->name = name;
            temp->max_bandwith= max_bandwith;

            temp->next = p->next;

            p->next = temp;

            if (p == last)
                last = temp;

            return last;
        }
        p = p->next;
    } while (p != last->next);


    return last;
}

//function of adding an apartment begining of the apartment circular linked list
struct node* addBegin(struct node* last, string name,int max_bandwith)
{
    if (last == 0){
        return addToEmpty(last, name, max_bandwith);
    }


    struct node* temp = new node;

    temp->name = name;
    temp->max_bandwith=max_bandwith;

    temp->next = last->next;
    last->next = temp;

    return last;
}

//remove an apartment from the circular apartment linked list
void remove_apartment(node* last, string name){
    struct node *p, *prev;

    if (last == 0)
        return;


    if((last)->name==name && (last)->next==last)
    {
        free(last);
        last=0;
        return;
    }

    if(last->name == name){
        p = last->next;
        while(p->next != last){
            p=p->next;
        }
        p->next = last->next;
        free(last);
        last = p;
        return;
    }

    if(last->next->name==name){
        p=last->next;
        last->next = p->next;
        free(p);
        p=0;
        return;
    }


    p=last->next;
    prev=last;
    do {

        if(p->name==name){
            prev->next=p->next;
            free(p);
            p=0;
            return;
        }
        prev = prev->next;
        p = p->next;
    } while (p != last->next);

    return;
}

//adding a flat begining to apartment node
struct node* add_flat_begin(node* last, string name, int index, int initial_bandwith, string flat_id){
    node* p = last->next; //head apartment

    fnode* flat = new fnode; //flat to add
    flat->index= index;
    flat->initial_bandwith=initial_bandwith;
    flat->flat_id= flat_id;

    do {

        if(p->name==name){
            p->fnext = flat;
            flat->next = 0;
        }
        p = p->next;

    } while (p != last->next);


    return last;
    }





//adding a flat to apartment node
struct node* add_flat(node* last, string name, int index, int initial_bandwith, string flat_id){

    node* p = last->next;
    fnode* flat = new fnode;
    fnode* fhead = last->fnext;
    flat->index= index;
    flat->initial_bandwith=initial_bandwith;
    flat->flat_id= flat_id;




    do {

        if(p->name==name){

            for(int i = 0; i< index-2 ;i++){
                fhead = fhead->next;
            }
            if (flat != 0 and fhead != 0) {
                flat->next = fhead->next;
                fhead->next = flat;
                flat->next=0;
            }


        }
        p = p->next;
    } while (p != last->next);

    return last;

}





//function of calculating the max bandwith
int find_sum_of_max_bandwidth(struct node* last){

    int sum_of_bandwith = 0;

    if (last == 0){
        return 0;
    }
    struct node *p;
    p = last->next;
    do {

        sum_of_bandwith+=p->max_bandwith;

        p = p->next;
    } while (p != last->next);


    return sum_of_bandwith;

}

//printing apartments and flats
void printList(node* last, ofstream& filename)
{

    node* p = last->next;
    fnode* fhead;


    if (last != 0) {

        do {
            filename << p->name << "("<< p->max_bandwith<<")"<<"    ";
            fhead = p->fnext;
            if(fhead != 0){

                filename<<"Flat"<<fhead->flat_id<<"("<<fhead->initial_bandwith<<")";

                while(fhead->next != 0){

                    filename<<fhead->next;
                    fhead = fhead->next;

                }
            }

            filename<<"\n";

            p = p->next;
        } while (p != last->next);
    }
    filename.close();
}













int main(int argc, char *argv[]) {


    struct node *last=0;
    fstream myfile;
    myfile.open(argv[1], ios::in);//open an input file
    ofstream outputFile(argv[2]);//open ana output file

    if(!myfile){
        cout<< "no such file!";
    }
    else {                                                    //inserting the input data to 2d matrix
        string line, temp;
        while (getline(myfile, line)) {

            data.push_back(arraystring ());


            istringstream strm(line);
            while (strm >> temp)

                data.back().push_back(temp);

        }
        for(int i = 0 ; i < data.size(); i++){
            if (data[i][0] == "add_apartment"){
                if(data[i][2]== "head"){
                    last = addBegin(last,data[i][1],stoi(data[i][3]));


                }

                if(data[i][2].substr(0,5)=="after"){
                    last = addAfter( last, data[i][1],stoi(data[i][3]), data[i][2].substr(6,1));

                }

                if(data[i][2].substr(0,6)=="before"){
                    last = addBefore( last, data[i][1],stoi(data[i][3]), data[i][2].substr(7,1));


                }

            }
            if(data[i][0]== "remove_apartment"){

                remove_apartment(last,data[i][1]);
            }
            if(data[i][0]== "find_sum_of_max_bandwidths"){
                int a = find_sum_of_max_bandwidth(last);
                outputFile<<"sum of bandwidth: "<<a<<endl<<endl;

            }

            if (data[i][0]=="add_flat"){

                if(data[i][2]=="0"){
                    last = add_flat_begin(last, data[i][1], stoi(data[i][2]), stoi(data[i][3]), data[i][4]);

                }
                else{
                    last = add_flat(last, data[i][1], stoi(data[i][2]), stoi(data[i][3]), data[i][4]);

                }

            }
            if(data[i][0]=="list_apartments"){
                printList(last,outputFile);

            }
        }

    }






    outputFile.close();
    myfile.close();

    return 0;
}
