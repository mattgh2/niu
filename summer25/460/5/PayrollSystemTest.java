// PayrollSystemTest.java
// Employee hierarchy test program.

import java.util.Scanner;
public class PayrollSystemTest { 
    private static final double BDAY_BONUS = 100.00;

   public static void main(String[] args) {
   
      // create subclass objects
      SalariedEmployee salariedEmployee = 
         new SalariedEmployee("John", "Smith", "111-11-1111", 800.00, new Date(6,15,1944));
      HourlyEmployee hourlyEmployee = 
         new HourlyEmployee("Karen", "Price", "222-22-2222", 16.75, 40, new Date(12,29,1960));
      CommissionEmployee commissionEmployee = 
         new CommissionEmployee(
         "Sue", "Jones", "333-33-3333", 10000, .06, new Date(9,8,1954));
      BasePlusCommissionEmployee basePlusCommissionEmployee = 
         new BasePlusCommissionEmployee(
         "Bob", "Lewis", "444-44-4444", 5000, .04, 300, new Date(3,2,1965));

      System.out.println("Employees processed individually:");
      
      System.out.printf("%n%s%n%s: $%,.2f%n%n", 
         salariedEmployee, "earned", salariedEmployee.earnings());
      System.out.printf("%s%n%s: $%,.2f%n%n",
         hourlyEmployee, "earned", hourlyEmployee.earnings());
      System.out.printf("%s%n%s: $%,.2f%n%n",
         commissionEmployee, "earned", commissionEmployee.earnings());
      System.out.printf("%s%n%s: $%,.2f%n%n", 
         basePlusCommissionEmployee, 
         "earned", basePlusCommissionEmployee.earnings());

      // create four-element Employee array
      Employee[] employees = new Employee[4]; 

      // initialize array with Employees
      employees[0] = salariedEmployee;
      employees[1] = hourlyEmployee;
      employees[2] = commissionEmployee; 
      employees[3] = basePlusCommissionEmployee;

      // Initialize a scanner to get the current month from the user.
      int current_month = getCurrentMonth();

      System.out.printf("\n\nEmployees processed polymorphically:%n%n");
      
      // generically process each element in array employees
      for (Employee currentEmployee : employees) {
      
         System.out.println(currentEmployee); // invokes toString

         // determine whether element is a BasePlusCommissionEmployee
         if (currentEmployee instanceof BasePlusCommissionEmployee) { 
         
            // downcast Employee reference to 
            // BasePlusCommissionEmployee reference
            BasePlusCommissionEmployee employee = (BasePlusCommissionEmployee) currentEmployee;

            employee.setBaseSalary(1.10 * employee.getBaseSalary());

            System.out.printf(
               "new base salary with 10%% increase is: $%,.2f%n", employee.getBaseSalary());
         } 
         System.out.printf("earned $%,.2f", currentEmployee.earnings());
         // Check if the current employee gets a birthday bonus.
         if (current_month == currentEmployee.getBirthDate().getMonth()) {
             System.out.printf("%s%.2f%s", " plus $",BDAY_BONUS," birthday bonus");
         }
         System.out.printf("%n%n");
      } 

      // get type name of each object in employees array
      for (int j = 0; j < employees.length; j++)
         System.out.printf("Employee %d is a %s%n", j, employees[j].getClass().getName()); 
   }
   /**
    * Gets the current month from stdin.
    * Will re-prompt if a valid month is not entered.
    */
   private static int getCurrentMonth() {
      Scanner input = new Scanner(System.in);
      int month = -1;
        while (month == -1) {
          System.out.print("Enter the current month (1 - 12): ");
          month = stoi(input.nextLine());

          if (month < 0 || month > 12) {
              month = - 1;
              System.out.println("\nInvalid month entered...");
          }
      }
      input.close();
      return month;
   }
   /**
    * Converts a String to an int, only deals in positive integers.
    * Returns -1 if String cannot be converted.
    */
   private static int stoi(String s) {
       int x = 0;
       for (int i = 0; i < s.length(); ++i) {
           char c = s.charAt(i);
           if (c < '0' || c > '9') 
               return -1;
           x = x * 10 + (c - '0');
       }
       return x;
   }
}
