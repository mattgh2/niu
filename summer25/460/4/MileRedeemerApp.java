
/*********************************************************
* CSCI 470/502      Assignment 1       Summer 2025       *
*                                                        *
* Developer(s):                                          *
*     Matt Warner                                        *
*                                                        *
* Due Date:                                              *
*     07/18/2025                                         *
*                                                        *
* Purpose:                                               *
*   Main app for the mile redeemer.
*                                                        *
**********************************************************/
import java.util.Scanner;
import java.io.IOException;
import java.io.File;
public class MileRedeemerApp {
    public static void main(String[] args) throws IOException {
        Scanner input = new Scanner(System.in);

        System.out.print("Please enter the name of the file: ");

        String file_name = input.nextLine();
        Scanner file_scanner = new Scanner(new File(file_name));

        System.out.println("-".repeat(65));
        System.out.printf("%10s%s%n", "", "WELCOME TO THE JAVA AIRLINES MILES REDEEMER APP");
        System.out.println("-".repeat(65));

        MileRedeemer redeemer = new MileRedeemer();

        redeemer.readDestinations(file_scanner);

        String[] available_citys = redeemer.getCityNames();

        // Display all available cities to the user.
        System.out.println("\nList of destination cities your client can travel to:\n");
        for (final String city : available_citys) {
            System.out.println(city);
        }
        System.out.println("\n" + "-".repeat(65));

        String process = "y";
        while (process.toLowerCase().equals("y")) {

            // Ask user for their Frequent Flyer Miles.
            System.out.print("Please enter your client's accumulated Frequent Flyer Miles: ");
            int user_miles = Integer.parseInt(input.nextLine());

            // Ask user for their month of departure.
            System.out.print("Please enter your client's month of departure (1-12): ");
            int departure_month = Integer.parseInt(input.nextLine());

            System.out.println("\nYour client's Frequent Flyer Miles can be used to redeem the following tickets: \n");

            // If there are cities available, display them to the user.
            String[] available_cities = redeemer.redeemMiles(user_miles, departure_month);
            if (available_cities.length > 0) {
                for (final String city : available_cities) {
                    System.out.println("*" + city);
                }
            }
            // else, tell the user that they do not have enough points to go anywhere.
            else {
                System.out.println("*** Your client has not accumulated enough Frequent Flyer Miles ***");

            }

            System.out.println("\nYour client's remaining Frequent Flyer Miles: " + redeemer.getRemainingMiles());


            // Prompt to continue; 
            System.out.println("\n" + "-".repeat(65));
            System.out.print("Do you want to continue (y/n)? ");
            process = input.nextLine();
            System.out.println("\n" + "-".repeat(65));
        }
        input.close();
        file_scanner.close();
    }

}
