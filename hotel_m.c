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
printf("2 > Deluxe Room   - Rs %d/night\n", deluxe_room);
printf("3 > Suite Room    - Rs %d/night\n", suite_room);
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
printf("          New Booking form          \n");
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
int mealPerDay = calc_meal_price(temp.add_breakfast, temp.add_lunch, temp.add_hightea, temp.add_dinner);
float total = (rmPrice * temp.stay_days) + (mealPerDay * temp.stay_days);
printf("\n====================================\n");
printf("             Bill Summary           \n");
printf("====================================\n");
printf("Room: Rs %.2f (%d x %d)\n", (float)(rmPrice * temp.stay_days), temp.stay_days, rmPrice);
printf("Meals: Rs %.2f (%d x %d)\n", (float)(mealPerDay * temp.stay_days), temp.stay_days, mealPerDay);
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
void list_bookings()
{
if (bookedCount == 0)
{
printf("\n No bookings to show.\n");
return;
}
printf("\n=========================================\n");
printf("             All Bookings (%d)           \n", bookedCount);
printf("=========================================\n");
for (int index = 0; index < bookedCount; index++)
{
printf("\n_____________________________________________________________________");
printf("\n %d > Booking #%d\n", index + 1, index + 1);
printf("     Name: %s\n", bookedList[index].customer_name);
printf("     Room: ");
if (bookedList[index].room_tier == 1) printf("Standard\n");
else if (bookedList[index].room_tier == 2) printf("Deluxe\n");
else printf("Suite\n");
printf("     Stay: Day %d -> Day %d\n", bookedList[index].in_date, bookedList[index].out_date);
printf("     Duration: %d days\n", bookedList[index].stay_days);
printf("     Status: In=%s | Out=%s\n",
bookedList[index].checked_IN ? "Yes" : "No",
bookedList[index].checked_OUT ? "Yes" : "No");
printf("     Total: Rs %.2f\n", bookedList[index].total_bill);
}
}
void handle_check()
{
if (bookedCount == 0)
{
printf("\nNo guests to update.\n");
return;
}
printf("\n=========================================\n");
printf("           Check-In / Check-Out          \n");
printf("=========================================\n");

for (int index = 0; index < bookedCount; index++)
{
printf("%d > %s ", index + 1, bookedList[index].customer_name);
printf(" > In:%s Out:%s\n",
bookedList[index].checked_IN ? "YES" : "NO",
bookedList[index].checked_OUT ? "YES" : "NO");
}
int quantity;
printf("\n  Select booking: ");
scanf("%d", &quantity);
quantity--;
if (quantity < 0 || quantity >= bookedCount)
{
printf("    Invalid booking.\n");
return;
}
int act;
printf("    1 > Check-In\n");
printf("    2 > Check-Out\n");
printf("    Action: ");
scanf("%d", &act);
if (act == 1)
{
if (bookedList[quantity].checked_IN)
printf("    Already checked in.\n");
else
{
bookedList[quantity].checked_IN = 1;
printf("    [./] Welcome, %s!\n", bookedList[quantity].customer_name);
}
}
else if (act == 2)
{
if (!bookedList[quantity].checked_IN)
printf("    Can't check out before check-in!\n");
else if (bookedList[quantity].checked_OUT)
printf("    Already checked out.\n");
else
{
bookedList[quantity].checked_OUT = 1;
printf("    [./] Goodbye, %s!\n", bookedList[quantity].customer_name);
printf("    Final Bill: Rs %.2f\n", bookedList[quantity].total_bill);
}
}
else
{
printf("Unknown action.\n");
}
save_to_file();
}
void delete_booking()
{
if (bookedCount == 0)
{
printf("\n  No bookings to delete.\n");
return;
}
list_bookings();
int idx;
printf("\n  Enter booking number to delete: ");
scanf("%d", &idx);
idx--;
if (idx < 0 || idx >= bookedCount)
{
printf("   Invalid booking number.\n");
return;
}
for (int i = idx; i < bookedCount - 1; i++)
{
bookedList[i] = bookedList[i + 1];
}
bookedCount--;
save_to_file();
printf("   [./] Booking deleted.\n");
}
int main()
{
int choice;
printf("\n=========================================\n");
printf("           Hotel Booking System          \n");
printf("=========================================\n");
load_from_file();
while (1)
{
printf("\n==============================\n");
printf("           Main menu          \n");
printf("==============================\n");
printf("\n1 > Create Booking\n");
printf("2 > Check-In\\Out\n");
printf("3 > View Bookings\n");
printf("4 > Delete Booking\n");
printf("5 > Exit\n");
printf("\n Choose: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
new_booking();
break;
case 2:
handle_check();
break;
case 3:
list_bookings();
break;
case 4:
delete_booking();
break;
case 5:
printf("\n[EXIT]\n");
return 0;
default:
printf("Invalid option.\n");
}
}
return 0;
}