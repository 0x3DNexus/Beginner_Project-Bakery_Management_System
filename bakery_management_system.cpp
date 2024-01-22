#include<iostream>
#include<string>
//using namespace std 

void placeOrder();
void recieveOrder();

typedef struct date{
    int day;
    int month;
    int year;
}date;

// template <int dynamic_size>

struct orderDetails{
    int orderNumber;
    std::string orderName;
    date orderDate;
};


class Orders{
    public:
        struct orderDetails o;
        Orders(){}

        virtual std::string* placeOrder() = 0; 

        void setDate(int& day, int& month, int& year){

            o.orderDate.day = day;
            o.orderDate.month = month;
            o.orderDate.year = year;
            
        }

        void setOrderDeatials(int& orderNumber, const std::string& orderName){
            o.orderNumber = orderNumber;
            o.orderName = orderName;
        }
        
        inline void displayDate(){
            std::cout<<"Order Date: "<<o.orderDate.day<<"/"<<o.orderDate.month<<"/"<<o.orderDate.year<<std::endl;
        }

        void recieveOrder(){
            displayDate();
            std::cout<<"Order Number: "<<o.orderNumber<<std::endl;
            std::cout<<"Order Name: "<<o.orderName<<std::endl;
        }

};

class orderItems : public Orders{
    private: 
        int current_order = 0;
        int max_order = 1;

    public:

        std::string getItem(){
            std::string item;
            std::cin>>item;

            return item;
        }

        std::string* placeOrder(){
            std::string* cart = new std::string[max_order];
            std::string* newArray = new std::string[max_order];

            while(true){
                std::cout<<(current_order + 1)<<". ";   //using current_order as a bullet numbering
                std::string item = getItem();
                
                if(item == "done"){break;}

                cart[current_order] = item;
                current_order += 1;
                max_order += 1;

                for(int x = 0; x < current_order; x++){
                    newArray[x] = cart[x];
                }

                delete[] cart;  //delete cart array
                cart = new std::string[max_order];  //create new cart array with increased size

                for(int x = 0; x < current_order; x++){
                    cart[x] = newArray[x];
                }

                delete[] newArray;  //delete newArray array
                newArray = new std::string[max_order]; //create new newArray array
            }

            delete[] newArray;
            return cart;
        }

        void displayOrderItems(std::string* newArray){
            std::cout<<std::endl;
            std::cout<<"Your Order: "<<std::endl;

            for(int x = 0; x < current_order; x++){
                std::cout<<(x + 1)<<". "<<newArray[x]<<std::endl;
            }
        }  
};

int placeOrRecieve(){
    //severe issue with character input dont try for fun

    int input = 0;

    std::cout<<"Would you Like to Place an Order or Recieve an Order?"<<std::endl;

    while(input != 1 && input != 2){
        std::cout<<"To Place an Order press [1] and to Recieve Order press [2]: ";
        std::cin>>input;
        std::cout<<std::endl;

        if(input != 1 && input != 2){
            std::cout<<"Invalid Input !!! Try Again"<<std::endl;
        }
    }
    return input;
}

int main(){
    std::cout<<std::endl;
    std::cout<<"***BAKERY MANAGEMENT SYSTEM***"<<std::endl;
    std::cout<<std::endl;

    int choice = placeOrRecieve();

    orderItems o1;
    std::string* ordereditems;

    if(choice == 1){

        int orderNum;
        std::string orderName;
        date d;

        std::cout<<"\nPlacing an Order !"<<std::endl;

        std::cout<<"\nGive order Number: ";
        std::cin>>orderNum;

        std::cout<<"\nEnter Name on the Order: ";
        std::cin>>orderName;

        std::cout<<"\nPlease Enter the date:\n"<<std::endl;
        std::cout<<"day: "; std::cin>>d.day;
        std::cout<<"month: "; std::cin>>d.month;
        std::cout<<"year: "; std::cin>>d.year;
        o1.setDate(d.day, d.month, d.year);

        std::cout<<std::endl;
        std::cout<<"Add your items to cart ! Type [done] when no more items left to add !"<<std::endl;

        o1.setOrderDeatials(orderNum, orderName);
        ordereditems = o1.placeOrder();

        int confirmation;
        std::cout<<"\nPress [1] to confirm your order and press [0] to cancel it: ";
        std::cin>>confirmation;

        if(confirmation == 1){
            std::cout<<"Order Confirmed Successfully !\n"<<std::endl;
        }
        else{
            std::cout<<"Order Cancelled !!!\n"<<std::endl;
            delete[] ordereditems;
        }
    }

    else if(choice == 2){
        std::cout<<"Here is your Order !\n"<<std::endl;

        o1.recieveOrder();
        o1.displayOrderItems(ordereditems);
    }

    int endChoice;
    std::cout<<"To recieve order press[4] to exit press[5]: ";
    std::cin>>endChoice;

    if(endChoice == 4){
        o1.recieveOrder();
        o1.displayOrderItems(ordereditems);
        delete[] ordereditems;
    }

    else{
        delete[] ordereditems;
    }

    return 0;
}