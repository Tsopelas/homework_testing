#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000000
#define MIN_NUMBER 1

// Συνάρτηση που ελέγχει αν ο αριθμός είναι πρώτος.
int is_prime(unsigned long long k) {
    // Χρησιμοποιείται η μέθοδος 6k+1 για αυτή την διαδικάσια.
    if (k < 2) {
        return 0;
    }
    if (k < 4){
        return 1;
    }
    if (k % 2 == 0 || k % 3 == 0){
        return 0;
    }
    // Το loop ξεκινάει απο το 5 και προσπερνά πολλούς αριθμούς που γνωρίζουμε πως δεν είναι πρώτοι.
    for (unsigned long long i = 5; i * i <= k; i += 6){
        if (k % i == 0 || k % (i + 2) == 0){
            return 0;
        }
    }
    return 1; // Επιστρέφουμε 1 αν ο αριθμός είναι πρώτος.
}

// Η συνάρτηση mirror υπολογίζει τον αντίστροφο ένος αριθμό.
unsigned long long mirror(unsigned long long n){
    unsigned long long mirrored = 0; //Αρχικοποιόυμε την μεταβλιτή που θα επιστρέψει τον αντίστροφο.
    while (n != 0) {
        mirrored = mirrored * 10 + n % 10;
        n /= 10;
    }
    //Μετα το loop επιστρέφουμε τον αντίστροφο.
    return mirrored;
  
}

// Η συνάρτηση check καλεί διαδοχικά όλες τις συναρτήσεις του προγράμματος και με βάση το αποτέλεσμα τους επιστρέφει 1 ή 0 στο αρχικό πρόγραμμα.
int check(unsigned long long n, unsigned long long i) {
    // Αν ένας αριθμός τελειώνει σε 0 τότε δεν έχει κατοπτρο (π.χ 1000 != 0001), γι' αυτό και εξαιρούνται στην αρχή του check.
    if (n % 10 != 0) {
        unsigned long long reversed = mirror(n); // Καλούμε την mirror για να πάρουμε τον αντίστροφο.
        if (reversed != n) {
            // Αν ο αριθμός δεν είναι παλινδρομικός, ελέγχουμε αν το τέλειο τετράγωνό του ειναι πρώτος.
            if (is_prime(i) == 1) {
                // Αν ναι, συνεχλιζουμε την διερεύνιση ελέγχοντας αν το τέλειο τετράγωνο του αντίστροφού του είναι επίσης πρώτος.
                unsigned long long rev_root = sqrt(reversed);
                if (rev_root * rev_root == reversed) {
                    if(is_prime(rev_root)) {
                        return 1; // Αν ισχύουν όλα τα παραπάνω επιστρέφουμε 1.
                    }
                }
            }
        }
    }
    
    return 0; // Αν όχι, τότε επιστρέφουμε 0, δηλαδή ο αριθμός δεν είναι κατοπτρικό τέλειο τετράγωνο.
}


// Η main διαβάζει, ελέγχει και υπολογίζει το sum με βάση τα inputs του χρήστη.
int main(int argc, char **argv) {
    // Ελέγχουμε αν ο χρήστης έχει δώσει ακριβώς 2 inputs και αν όχι επιστρέφουμε error.
    if (argc != 3) {
        printf("ERROR: MORE/LESS THAN 2 INPUTS\n");
        return 1;
    }
    // Εκχωρούμε τα inputs του χρήστη στις μεταβλήτες low και high.
    unsigned long long low = atoll(argv[1]);
    unsigned long long high = atoll(argv[2]);
    // Ελέγχουμε αν οι αριθμοί ανήκουν στο [1,10^15].
    if (low > high || low < MIN_NUMBER || high > MAX_NUMBER) {
        printf("INPUTS NEED TO MATCH THE LIMITS\n");
        return 1;
    }
    // Η παρακάτω διαδικασία βρίσκει το πρώτο τετράγωνο στο διάστημα που έδωσε ο χρήστης για να ξεκινήσει το loop απο αυτό.
    unsigned long long begin = sqrt(low);
    if (begin * begin < low) {
        ++begin; 
    }
    long long sum = 0; // Αρχικοποίηση του αθροίσματος των κατοπτρικών πρώτων τετραγώνων.
    //Το παρακάτω loop ξεκινάει από το πρώτο τετράγωνο στο διάστημα που έδωσε ο χρήστης και ελέγχει μόνο τα τέλεια τετράγωνα, καθώς αυτά μας ενδιαφέρουν.
    for (unsigned long long i = begin; i * i <= high; i += 2) {
        register unsigned long long sqr = i * i;
        // Καλούμε την check.
        if (check(sqr,i)) {
            sum += sqr;
        }
    }
    printf("%lld\n",sum); // Εκτυπώνουμε το αποτέλεσμα της διαδικασίας.
    return 0;
}
