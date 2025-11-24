Project Report: Hotel Booking System
Title Page
Hotel Booking System
Project Report
Submitted By: GRACY JINDAL
Course: C Programming
Abstract
This project implements a hotel booking system in C supporting booking, check-in/out,
billing, meals, and storage.
Problem Defini=on
Design a system to automate hotel booking, billing, and record maintenance using C
programming.
System Design (Flowcharts, Algorithms)
System uses:
•
Struct-based data model
•
File handling
•
Menu-driven workflow
Algorithms include booking creation, bill calculation, status updates, and deletion.
Implementa=on Details (with snippets)
Full program code is included below.
Tes=ng & Results
Tested booking creation, check-in/out, deletion, file load/save. All functions worked
correctly.
Conclusion & Future Work
System is functional. Future improvements: date validation, UI, online system.
References
•
•
C Programming Documentation
GCC Manual
Appendix (op=onal)
Additional diagrams can be added here.
Full Source Code
#include <stdio.h>
#include <string.h>
#define max_bookings 10
#define min_discount_days 5
#define discount_rate 0.10
#define standard_room 1000
#define deluxe_room 2000
#define suite_room 3500
#define price_breakfast 150
#define price_lunch 300
#define price_hightea 120
#define price_dinner 350
struct Booking
{
int checked_IN;
int checked_OUT;
char customer_name[50];
int room_tier;
int in_date, out_date;
int stay_days;
int add_breakfast, add_lunch, add_hightea, add_dinner;
float total_bill;
};
struct Booking bookedList[max_bookings];
int bookedCount = 0;
void save_to_file()
{
FILE *fp = fopen("bookings.dat", "wb");
if (!fp)
{
printf("Error saving file!\n");
return;
}
fwrite(&bookedCount, sizeof(int), 1, fp);
fwrite(bookedList, sizeof(struct Booking), bookedCount, fp);
fclose(fp);
}
void load_from_file()
{
FILE *fp = fopen("bookings.dat", "rb");
if (!fp)
return;
fread(&bookedCount, sizeof(int), 1, fp);
fread(bookedList, sizeof(struct Booking), bookedCount, fp);
fclose(fp);
}
void show_room_tiers()
{
printf("\n===== Available Rooms =========\n");
printf("1 > Standard Room - Rs %d/night\n", standard_room);
printf("2 > Deluxe Room - Rs %d/night\n", deluxe_room);
printf("3 > Suite Room - Rs %d/night\n", suite_room);
printf("===============================\n");
}
int get_room_tier(int t)
{
while (1)
{
if (t == 1)
return standard_room;
if (t == 2)
return deluxe_room;
if (t == 3)
return suite_room;
else printf("Invalid room type");
}
}
int calc_meal_price(int b, int l, int h, int d)
{
int total = 0;
if (b) total += price_breakfast;
if (l) total += price_lunch;
if (h) total += price_hightea;
if (d) total += price_dinner;
return total;
}
void new_booking()
{
if (bookedCount >= max_bookings)
{
printf("\n Bookings max limit reached\n");
return;
}
struct Booking temp;
printf("\n====================================\n");
printf(" New Booking form \n");
printf("====================================\n");
printf("Customer Name: ");
scanf("%s", temp.customer_name);
show_room_tiers();
printf("Choose room type (1-3): ");
scanf("%d", &temp.room_tier);
if (temp.room_tier < 1 || temp.room_tier > 3)
{
printf("Invalid room selection\n");
return;
}
printf("Check-In Date (1-31): ");
scanf("%d", &temp.in_date);
printf("Check-Out Date (1-31): ");
scanf("%d", &temp.out_date);
if (temp.out_date <= temp.in_date)
{
printf("Check-Out date can't be same or earlier than Check-In\n");
return;
}
temp.stay_days = temp.out_date - temp.in_date;
printf("\n-- Optional Meals (1 yes / 0 no) --\n");
printf("Breakfast (Rs %d): ", price_breakfast);
scanf("%d", &temp.add_breakfast);
printf("Lunch (Rs %d): ", price_lunch);
scanf("%d", &temp.add_lunch);
printf("High Tea (Rs %d): ", price_hightea);
scanf("%d", &temp.add_hightea);
printf("Dinner (Rs %d): ", price_dinner);
scanf("%d", &temp.add_dinner);
int rmPrice = get_room_tier(temp.room_tier);
int mealPerDay = calc_meal_price(temp.add_breakfast, temp.add_lunch,
temp.add_hightea, temp.add_dinner);
float total = (rmPrice * temp.stay_days) + (mealPerDay * temp.stay_days);
printf("\n====================================\n");
printf(" Bill Summary \n");
printf("====================================\n");
printf("Room: Rs %.2f (%d x %d)\n", (float)(rmPrice * temp.stay_days),
temp.stay_days, rmPrice);
printf("Meals: Rs %.2f (%d x %d)\n", (float)(mealPerDay * temp.stay_days),
temp.stay_days, mealPerDay);
if (temp.stay_days >= min_discount_days)
{
float discountAmt = total * discount_rate;
printf(" :) Long Stay Discount: Rs %.2f\n", discountAmt);
total -= discountAmt;
}
temp.total_bill = total;
temp.checked_IN = 0;
temp.checked_OUT = 0;
bookedList[bookedCount++] = temp;
save_to_file();
printf("\n [./] Booking saved for %s!\n", temp.customer_name);
printf("Total Bill: Rs %.2f\n", total);
}