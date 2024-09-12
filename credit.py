# This program tests card numbers to see if they are valid and prints which company the card is under

from cs50 import get_int


def main():

    # Asks the user for the card number
    cc = get_int("Number: ")

    # Calculates checksum
    validate = checksum(cc)

    # If last digit of calculated checksum is 0
    if validate == 0:

        # Check company of card number
        company = check_company(cc)

        # Print corresponding company based on value of check_company function
        if company == 1:
            print("AMEX")

        elif company == 2:
            print("MASTERCARD")

        elif company == 3:
            print("VISA")

        else:
            print("INVALID")

    # If last digit of checksum is not 0 print INVALID
    else:
        print("INVALID")


def checksum(cc):

    # Initialize the sum of even and odd numbers
    even_sum = 0
    odd_sum = 0

    # While the card number is greater than 0
    while cc > 0:

        # Retrieve last digit
        mod = cc % 10
        # Add to sum of even digits
        even_sum += mod
        # Move one digit over
        cc = cc // 10
        # Retrieve last digit
        mod = cc % 10
        # Multiply odd digit by 2
        multiply = mod * 2

        # If odd digit multiplied by 2 is greater than a single digit
        if multiply > 9:
            # Retrieve last digit of multiplied number
            multiply = multiply % 10
            # Add last digit to 1 as 18 is the highest number a single digit times 2 can equal
            odd_sum += multiply + 1

        # If odd digit multipllied by 2 is a single digit
        else:
            # Add digit to the sum of all other odd numbers
            odd_sum += multiply

        # Move one digit over
        cc = cc // 10

    # Add sum of even and odd digits together
    validate = even_sum + odd_sum
    # Calculate last digit of validate
    validate = validate % 10
    # Return validate
    return validate


def check_company(cc):

    # Initialize number of digits
    digits = 0

    # While card number is greater than 0
    while cc > 0:

        # If three digits or more left
        if cc > 99:
            # Remove last digit
            cc = cc // 10
            # Add to digit count
            digits += 1

        # If two digits or more left
        elif cc > 9:
            # Store last digit (second digit of card number)
            mod1 = cc % 10
            # Remove last digit
            cc = cc // 10
            # Add to digit count
            digits += 1

        # If one digit left
        else:
            # Store last digit (first digit of card number)
            mod2 = cc % 10
            # Remove last digit
            cc = cc // 10
            # Add to digit count
            digits += 1

    # Returns card company based on total digits and what the first and second digit of cc is
    if digits == 15 and mod2 == 3 and (mod1 == 4 or mod1 == 7):

        # AMEX
        company = 1

    elif digits == 16 and mod2 == 5 and (mod1 == 1 or mod1 == 2 or mod1 == 3 or mod1 == 4 or mod1 == 5):

        # MASTERCARD
        company = 2

    elif digits == 13 or digits == 16 and mod2 == 4:

        # VISA
        company = 3

    else:

        # INVALID
        company = 4

    # Return company
    return company


main()
