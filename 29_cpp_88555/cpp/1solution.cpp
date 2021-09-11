#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <numeric>

using namespace std;

string Serial;
string Name;
string Price;
int customer_number;
int quantity;
string answer;
string response;

// Total of Individual items and Grand Total

float total;
float individual_total;

float total_salad;
float total_fried_rice;
float total_noodle_soup;
float total_beef_noodle_soup;
float total_century_egg_pork_lean_congee;
float total_sea_food_congee;
float total_peking_duck;
float total_bbq_duck;
float total_lettuce_with_soy_sauce;
float total_broccoli_with_oyester_sauce_sweet_sour_pork;
float total_sweet_and_sour_pork;
float total_braised_beef;
float total_braised_pork;
float total_braised_fish;
float total_steamed_fish;
float total_spicy_crab;
float total_chefs_daily_soup;
float total_hot_and_sour_soup;
float total_seafood_tofu_soup;
float total_bbq_meat;

void selection();

void salad();
void fried_rice();
void noodle_soup();
void beef_noodle_soup();
void century_egg_pork_lean_congee();
void sea_food_congee();
void peking_duck();
void bbq_meat();
void bbq_duck();
void lettuce_with_soy_sauce();
void broccoli_with_oyester_sauce_sweet_sour_pork();
void sweet_and_sour_pork();
void braised_beef();
void braised_pork();
void braised_fish();
void steamed_fish();
void spicy_crab();
void chefs_daily_soup();
void hot_and_sour_soup();
void seafood_tofu_soup();

void again();

void grand_total();

void reset();


void showlist(list <float> g)
{
    list <float> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

list <float> bill_list;

int main(){
    

    ifstream ip("menu-0c2enziu.csv");
    
    if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

    while(ip.good()){

        getline(ip,Serial,',');
        getline(ip,Name,',');
        getline(ip,Price,'\n');

        std::cout << Serial << " " << Name << " " << Price << '\n';
    
    }
    ip.close();

    cout << "Continue? ";
    cout << "yes or no\n";
    cin >> response;

    if ((response) == "yes")
    {
        cout << "Enter customer number: ";
        cin >> customer_number;
        reset();
        selection(); 
    }
    else if ((response) == "no")
    {
        float sum = std::accumulate(std::begin(bill_list), std::end(bill_list), 0.0);
        printf("Total for past 24 hours: %.2f", sum);
    }   
    
       
}

void selection()
{
    int Serial_;
    
    cout << "Enter your choice of food in Serial number : ";
    cin >> Serial_;

    if ((Serial_) == 1)
    {
        salad();
    }
    else if ((Serial_) == 2)
    {
        fried_rice();
    }
    else if ((Serial_) == 3)
    {
        noodle_soup();
    }
    else if ((Serial_) == 4)
    {
        beef_noodle_soup();
    }
    else if ((Serial_) == 5)
    {
        century_egg_pork_lean_congee();
    }
    else if ((Serial_) == 6)
    {
        sea_food_congee();
    }
    else if ((Serial_) == 7)
    {
        peking_duck();
    }
    else if ((Serial_) == 8)
    {
        bbq_meat();
    }
    else if ((Serial_) == 9)
    {
        bbq_duck();
    }
    else if ((Serial_) == 10)
    {
        lettuce_with_soy_sauce();
    }
    else if ((Serial_) == 11)
    {
        broccoli_with_oyester_sauce_sweet_sour_pork();
    }
    else if ((Serial_) == 12)
    {
        sweet_and_sour_pork();
    }
    else if ((Serial_) == 13)
    {
        braised_beef();
    }
    else if ((Serial_) == 14)
    {
        braised_pork();
    }
    else if ((Serial_) == 15)
    {
        braised_fish();
    }
    else if ((Serial_) == 16)
    {
        steamed_fish();
    }
    else if ((Serial_) == 17)
    {
        spicy_crab();
    }
    else if ((Serial_) == 18)
    {
        chefs_daily_soup();
    }
    else if ((Serial_) == 19)
    {
        hot_and_sour_soup();
    }
    else if ((Serial_) == 20)
    {
        seafood_tofu_soup();
    }
    else 
    {
        printf("Invalid Input, Please check the menu and try again !!");
        selection();
    }
}

void salad()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_salad = 8.99 * quantity;
    printf("Your total amount is %.2f Dolars, Please pay at the counter\n ", total_salad);
    again();
}

void fried_rice()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_fried_rice = 12.99 * quantity;
    printf("Your total amount is %.2f Dollar, Please pay at the counter\n\n\n ", total_fried_rice);
    again();
}

void noodle_soup()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_noodle_soup = 10 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_noodle_soup);
    again();
}

void beef_noodle_soup()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_beef_noodle_soup = 15.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_beef_noodle_soup);
    again();
}

void century_egg_pork_lean_congee()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_century_egg_pork_lean_congee = 8.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_century_egg_pork_lean_congee);
    again();
}

void sea_food_congee()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_sea_food_congee = 12.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_sea_food_congee);
    again();
}

void peking_duck()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_peking_duck = 52.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_peking_duck);
    again();
}

void bbq_meat()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_bbq_meat = 15.99 * quantity;
    printf("Your total amount is %.2f , Please pay at the counter\n\n\n ", total_bbq_meat);
    again();
}

void bbq_duck()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_bbq_duck = 19.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_bbq_duck);
    again();
}

void lettuce_with_soy_sauce()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_lettuce_with_soy_sauce = 12.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_lettuce_with_soy_sauce);
    again();
}

void broccoli_with_oyester_sauce_sweet_sour_pork()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_broccoli_with_oyester_sauce_sweet_sour_pork = 12.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_broccoli_with_oyester_sauce_sweet_sour_pork);
    again();
}

void sweet_and_sour_pork()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_sweet_and_sour_pork = 21.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_sweet_and_sour_pork);
    again();
}

void braised_beef()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_braised_beef = 26.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_braised_beef);
    again();
}

void braised_pork()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_braised_pork = 21.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_braised_pork);
    again();
}

void braised_fish()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_braised_fish = 36.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_braised_fish);
    again();
}

void steamed_fish()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_steamed_fish = 32.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_steamed_fish);
    again();
}

void spicy_crab()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_spicy_crab = 56.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_spicy_crab);
    again();
}

void chefs_daily_soup()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_chefs_daily_soup = 6.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_chefs_daily_soup);
    again();
}

void hot_and_sour_soup()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_hot_and_sour_soup = 8.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_hot_and_sour_soup);
    again();
}

void seafood_tofu_soup()
{
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    total_seafood_tofu_soup = 12.99 * quantity;
    printf("Your total amount is %.2f Dollars, Please pay at the counter\n\n\n ", total_seafood_tofu_soup);
    again();
}

void again()
{
    // grand_total();
    int again = 0;
    printf("\nWould you like to buy anything else?\n[1] Yes , [2] No : "); 
    scanf("%d", &again);
    system("cls");
    if (again == 1)
    {
        selection();
    }
    else if (again == 2)
    {  
        grand_total();
        
        printf("\n");
        printf("\nBilling list:");
        showlist(bill_list);
        main();
    }
    else
    {
        printf("Invalid Selection");
    }
}

void grand_total()
{
    float total = total_salad + total_fried_rice + 
                                total_noodle_soup + 
                                total_beef_noodle_soup + 
                                total_century_egg_pork_lean_congee + 
                                total_sea_food_congee + 
                                total_peking_duck + 
                                total_bbq_duck + 
                                total_lettuce_with_soy_sauce + 
                                total_broccoli_with_oyester_sauce_sweet_sour_pork + 
                                total_sweet_and_sour_pork + 
                                total_braised_beef + 
                                total_braised_pork + 
                                total_braised_fish + 
                                total_steamed_fish + 
                                total_spicy_crab + 
                                total_chefs_daily_soup + 
                                total_hot_and_sour_soup + 
                                total_seafood_tofu_soup;
    printf("Grand Total: %.2f", total);

    float individual_total = total / customer_number;

    printf("\nIndividual Total: %.2f", individual_total);

    bill_list.push_back(total);

}

void reset()
{
    float total = 0;
    float individual_total = 0;
    float total_salad = 0;
    float total_fried_rice = 0;
    float total_noodle_soup = 0;
    float total_beef_noodle_soup = 0;
    float total_century_egg_pork_lean_congee = 0;
    float total_sea_food_congee = 0;
    float total_peking_duck = 0;
    float total_bbq_duck = 0;
    float total_lettuce_with_soy_sauce = 0;
    float total_broccoli_with_oyester_sauce_sweet_sour_pork = 0;
    float total_sweet_and_sour_pork = 0;
    float total_braised_beef = 0;
    float total_braised_pork = 0;
    float total_braised_fish = 0;
    float total_steamed_fish = 0;
    float total_spicy_crab = 0;
    float total_chefs_daily_soup = 0;
    float total_hot_and_sour_soup = 0;
    float total_seafood_tofu_soup = 0;
    float total_bbq_meat = 0;
}


  