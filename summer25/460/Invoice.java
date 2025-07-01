/*********************************************************
* CSCI 470/502      Assignment 2       Summer 2025       *
*                                                        *
* Developer(s):                                          *
*     Matt Warner                                        *
*                                                        *
* Due Date:                                              *
*     06/27/2025                                         *
*                                                        *
* Purpose:                                               *
*      Invoice class for a hardware store                *
*                                                        *
**********************************************************/
public class Invoice {

    /**
     * Default Constructor.
     */
    public Invoice() {
        part_number = "";
        part_description = "";
        uantity = 0;
        price_per_item = 0;
    }
    /**
     * Invoice Constructor.
     */
    public Invoice(String part_number, String part_description, int quantity, double price_per_item) {
        this.part_number = part_number;
        this.part_description = part_description;
        this.quantity = quantity;
        this.price_per_item = price_per_item;
    }
    /**
     * Sets Part Number.
     */
    public void setPartNumber(String part_number) {
        this.part_number = part_number;
    }
    /**
     * Sets Part Desc.
     */
    public void setPartDescription(String part_description) {
        this.part_description = part_description;
    }
    /**
     * Sets Quantity.
     */
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
    /**
     * Sets Price Per Item.
     */
    public void setPricePerItem(double price_per_item) {
        this.price_per_item = price_per_item;
    }
    /**
     * Returns Part Number.
     */
    public String getPartNumber() {
        return part_number;
    }
    /**
     * Returns Part Description.
     */
    public String getPartDescription() {
        return part_description;
    }
    /**
     * Returns Quantity.
     */
    public int getQuantity() {
        return quantity;
    }
    /**
     * Returns Price Per Item.
     */
    public double getPricePerItem() {
        return price_per_item;
    }
    /**
     * Returns calculated Invoice Amount.
     */
    public double getInvoiceAmount() {
        if (quantity < 0) quantity = 0;
        if (price_per_item < 0.0) price_per_item = 0.0;
        return quantity * price_per_item;
    } 

    private String part_number;
    private String part_description;
    private int quantity;
    private double price_per_item;

};

