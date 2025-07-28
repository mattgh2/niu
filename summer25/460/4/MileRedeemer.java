/********************************************************* 
 * CSCI 470/502      Assignment 4       Summer 2025       *
* Developer(s):                                          *
*     Matt Warner                                        *
*                                                        *
* Due Date:                                              *
*     7/18/2025                                         *
*                                                        *
* Purpose:                                               *
*      Encapsulates logic for redeeming miles.          *
*                                                        *
**********************************************************/
import java.util.Scanner;
import java.util.ArrayList;
import java.io.IOException;
import java.util.Comparator;
import java.util.Arrays;
import java.util.HashMap;
public class MileRedeemer {

    private static final int DESTINATION = 0;
    private static final int NORMAL_MILEAGE = 1;
    private static final int SUPER_SAVER_MILEAGE = 2;
    private static final int MILEAGE_UNTIL_UPGRADE = 3;
    private static final int START_OFF_SEASON = 0;
    private static final int END_OFF_SEASON = 1;


    public Destination[] destinations;
    private int remaining_miles;

    /**
     * Constructors.
     */ 
    MileRedeemer() {
        destinations = new Destination[0];
        remaining_miles = 0; 
    }
    MileRedeemer(int remaining_miles) {
        this.remaining_miles = remaining_miles;
    }
    /**
     * Reads from file containing information about destinations.
     * Fills @field destinations with destination objs created from file data.
     */
    public void readDestinations(Scanner file_scanner) throws IOException {
       String current_line;
       ArrayList<Destination> dest = new ArrayList<Destination>();

       // Reads each line from file line by line, appending
       while (file_scanner.hasNextLine()) {
           current_line = file_scanner.nextLine();

           Destination destination = createDestinationObj(current_line);
           dest.add(destination);
       }

       // Convert ArrayList of destinations to fixed size array.
       destinations = dest.toArray(new Destination[dest.size()]);
       Arrays.sort(destinations, new MileageComparator());
    }
    /**
     * Returns a String array of all city names that are available.
     */
    public String[] getCityNames() {
        ArrayList<String> temp_city_names = new ArrayList<String>();

        // Iterate through all destination objects stored in @field destinations, adding only the city name.
        for (final Destination destination : destinations) {
            temp_city_names.add(destination.getDestination());
        }
        temp_city_names.sort(Comparator.naturalOrder());

        return temp_city_names.toArray(new String[temp_city_names.size()]);
    }
    /**
     * Algorithm to determine which destinations the user can travel to. 
     */
    public String[] redeemMiles(int miles, int month) {

        ArrayList<String> can_travel = new ArrayList<String>();

        // Used as a Parallel array to can_travel to store upgrade costs.
        ArrayList<Integer> cost_to_upgrade = new ArrayList<Integer>(); 

        // Stores if each destination is economy or First class.
        HashMap<String,Character> travel_type = new HashMap<String,Character>();

        for (final Destination destination : destinations) {

            // Get the amount of mileage required for traveling to this destination.
            int miles_required = (month >= destination.getStartOffSeason() && month <= destination.getEndOffSeason()) 
                ? destination.getSuperSaverMileage() : destination.getNormalMileage();

            // Check if the current destination is available.
            if (miles >= miles_required) {

                can_travel.add(destination.getDestination());
                cost_to_upgrade.add(destination.getMileageUntilUpgrade());
                travel_type.put(destination.getDestination(), 'E');

                miles -= miles_required;
            }
        }
        // Check for potential upgrades.
        for (int i = 0; i < cost_to_upgrade.size(); ++i) {
            int upgrade_cost = cost_to_upgrade.get(i);
            if (miles >= upgrade_cost) {
                miles -= upgrade_cost;

                // Reinsert the destination with the upgraded travel class.
                travel_type.put(can_travel.get(i), 'F');
            }
        }
        // Update @field remaining miles to what the client has left.
        this.remaining_miles = miles;

        String[] available_destinations = new String[travel_type.size()];
        // Iterate through all destinations, adding them to the array being returned;
        for (int i = 0; i < can_travel.size(); ++i) {
            available_destinations[i] = "A trip to " + can_travel.get(i) + " " + ((travel_type.get(can_travel.get(i)) == 'E') ? "Economy Class" : "First Class");
        }

        return available_destinations;
    }
    public int getRemainingMiles() {
        return remaining_miles;
    }
    /**
     * Creates a Destination object from a line of file data.
     */
    private Destination createDestinationObj(String data) {
           // spliting the string into tokens deliminated by semicolons.
           String[] tokens = data.split(";");

           // Getting the off season interval from the back of the array.
           String[] off_season_interval = tokens[tokens.length - 1].split("-");

           Destination destination = new Destination(
                   tokens[DESTINATION],
                   Integer.parseInt(tokens[NORMAL_MILEAGE]),
                   Integer.parseInt(tokens[SUPER_SAVER_MILEAGE]),
                   Integer.parseInt(tokens[MILEAGE_UNTIL_UPGRADE]),
                   Integer.parseInt(off_season_interval[START_OFF_SEASON]),
                   Integer.parseInt(off_season_interval[END_OFF_SEASON])
                   );
           return destination;
    }

    /**
     * Custom Comparator for Destination objects.
     * Sorts asc by normal_mileage.
     */
    private class MileageComparator implements Comparator<Destination> {
        @Override
        public int compare(Destination d1, Destination d2) {
            return d2.getNormalMileage() - d1.getNormalMileage();
        }
    }

}
