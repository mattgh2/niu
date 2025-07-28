/*********************************************************
* CSCI 470/502      Assignment 1       Summer 2025       *
*                                                        *
* Developer(s):                                          *
*     Matt Warner                                        *
*                                                        *
* Due Date:                                              *
*     06/20/2025                                         *
*                                                        *
* Purpose:                                               *
*      Adds Two numbers                                  *
*                                                        *
**********************************************************/

public class Destination {
    private String destination;
    private int normal_mileage;
    private int super_saver_mileage;
    private int mileage_until_upgrade;
    private int start_off_season;
    private int end_off_season;


    /**
     * Constructors.
     */
    Destination() {
        destination = "";
        normal_mileage = 0; 
        super_saver_mileage = 0;
        mileage_until_upgrade = 0;
        start_off_season = 0;
        end_off_season = 0;
    }
    Destination(String destination, int normal_mileage, int super_saver_mileage, 
                int mileage_until_upgrade, int start_off_season, int end_off_season) 
    {
        this.destination = destination;
        this.normal_mileage = normal_mileage;
        this.super_saver_mileage = super_saver_mileage;
        this.mileage_until_upgrade = mileage_until_upgrade;
        this.start_off_season = start_off_season;
        this.end_off_season = end_off_season;
    }

    /**
     * Accessor Methods.
     */
    public String getDestination() {
        return destination;
    }
    public int getNormalMileage() {
        return normal_mileage;
    }
    public int getSuperSaverMileage() {
        return super_saver_mileage;
    }
    public int getMileageUntilUpgrade() {
        return mileage_until_upgrade;
    }
    public int getStartOffSeason() {
        return start_off_season;
    }
    public int getEndOffSeason() {
        return end_off_season;
    } 

    /**
     * Mutator Methods.
     */
    public void getDestination(String destination) {
        this.destination = destination;
    }
    public void setNormalMileage(int normal_mileage) {
        this.normal_mileage = normal_mileage;
    }
    public void setSuperSaverMileage(int super_saver_mileage) {
        this.super_saver_mileage = super_saver_mileage;
    }
    public void setMileageUntilUpgrade(int mileage_until_upgrade) {
        this.mileage_until_upgrade = mileage_until_upgrade;
    }
    public void setStartOffSeason(int start_off_season) {
        this.start_off_season = start_off_season;
    }
    public void setEndOffSeason(int end_off_season) {
        this.end_off_season = end_off_season;
    } 

};

