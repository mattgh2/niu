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
*      Test program for Invoice class                    *
*                                                        *
**********************************************************/
import java.text.DecimalFormat;

public class InvoiceTest {
    /**
     * Prints an Invoice.
     */
    public static void printInvoice(Invoice invoice, int invoice_number) {
        String price_format_pattern = "###,###,##0.00";
        String subtotal_format_pattern = "$##,###,##0.00";

        DecimalFormat item_price_format = new DecimalFormat(price_format_pattern);
        DecimalFormat subtotal_format = new DecimalFormat(subtotal_format_pattern);

        System.out.printf("%s%d%n", "Invoice #", invoice_number);
        System.out.printf("%s%s%n", "Part No.: ", invoice.getPartNumber());
        System.out.printf("%s%s%n", "Item Desc.: ",invoice.getPartDescription());
        System.out.printf("%s%d%n", "Quantity:  ",invoice.getQuantity());
        System.out.printf("%s%s%n", "Item Price: ",item_price_format.format(invoice.getPricePerItem()));
        System.out.printf("%s%s%n%n", "Invoice Subtotal:  ",subtotal_format.format(invoice.getInvoiceAmount()));
    }

    public static void main(String[] args) {
        Invoice invoice_test_1 = new Invoice("01","Hammer", 999, 2);
        printInvoice(invoice_test_1,1);

        Invoice invoice_test_2 = new Invoice("02","Cordless Drill", 10, 189);
        printInvoice(invoice_test_2,2);

        Invoice invoice_test_3 = new Invoice("03","Pickaxe", 100, 999999.999);
        printInvoice(invoice_test_3,3);

        Invoice invoice_test_4 = new Invoice("04","Shovel", -1, 20);
        printInvoice(invoice_test_4,4);

        Invoice invoice_test_5 = new Invoice("05","Chainsaw", -4,-4);
        printInvoice(invoice_test_5,5);
    }

};
