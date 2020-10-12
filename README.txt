1115201700076
ΜΑΝΤΖΟΥΡΑΝΗΣ ΓΙΩΡΓΟΣ


compilation:
	make
εκτέλεση:
	./main [χωριτηκότητα] [αριθμός_χώρων_επιβατών]
διαγραφή εκτελέσιμου και .o αρχείων :
	make clean


Για τις clone() συναρτήσεις, επιστρέφω ένα αντικέιμενο του new [Object(*this)], όπου Object είναι κάθε φορά
αντικείμενο από τις κλάσσεις που με ενδιαφέρει. Στις Object,Employee,PrivateCompartment,PlaneComponent είναι
pure virtual συνάρτηση. Για να καταφέρω να πετύχω deep copy έχω ορίσει σε κάθε συνάρτηση έναν copy_constructor και
από έναν copy assignment operator ενώ κάθε φορά που γίνεται cloned ένα αντικείμενο προσέχω να αντιγράφω και τα id's τους.

Οι κλάσσεις Object,Employee,PlaneComponent είναι abstract. Επίσης όσον αφορά τις πρώτες δύο τα
μέλη τους έχω επιλέξει να είναι protected έτσι ώστε να είναι προσπελάσιμα και από τις υποκλάσσεις τους.

Οι κλάσεις EquipmentCompartment, CargoBay, PassengerCompartment κληρονομούν αρχικά από τις 
PrivateCompartment και PlaneComponent, με την τελευταία να κληρονομεί από το Object. Επομένως
υπάρχει μια Multilevel ιεραρχία. Κάθε φορά που δημιουργείται ένα αντικείμενο, υπάρχει μια gloabl 
ακέραια μεταβλητή που αυξάνεται και δίνεται ως παράμετρος στον Constructor του Object. Επίσης να σημειω-
θεί ότι ο Destructor του Object είναι virtual. 
Ακόμη έχω επιλέξει όταν καλείται η toString() για οποιοδήποτε κλάσση να δίνεται ως παράμετρος ένα 
αντικείμενο τύπου SString, του οποίου το data member str(char*) δείχνει σε NULL τιμή, έτσι ώστε 
να αρχικοποιείται κατάλληλα από την Object::toString(SString*) που καλείται κάθε φορά, για να φαίνεται
η ιεραρχία. 


Στο plane υπάρχει ως data member ένας δείκτης σε SString* desc, που κατά τη δημιουργία του αεροπλάνου
έχει πάντα την τιμή [Plane] και δεν έχει να κάνει καμία σχέση με την περιγραφή που επιστρέφει η toString,
διότι δεν θεώρησα σημαντικό να κρατάω στην desc το αποτέλεσμα της toString. Επίσης να σημειωθεί ότι 
για την χωριτηκότητα και για τον αριθμό των χώρων επιβατών θα πρέπει ο χρήστης να δίνει από τη γραμμή
εντολών 2 αριθμόυς όπου ο πρώτος θα είναι η χωριτηκότητα και ο δεύτερος ο αριθμός των χώρων επιβατών.

Η κλάσση PassengerCompartment έχει ως data member έναν δείκτη σε PassengerCompartment και κατά τη δημιουργία
του αεροπλάνου επιλέγεται τυχαία ποιος από τους χώρους επιβατών θα έχει εσωτερικό χώρο. (ο εσωτερικός χώρος
θα είναι 1 κάθε φορά, δηλαδή ο εσωτερικός χώρος δεν θα έχει άλλον εσωτερικό χώρο). Ακόμη η κλάσση αυτή έχει
ως private member έναν ακέραιο αριθμό που μας δείχνει τον αριθμό του χώρου επιβατών στον οποίο είμαστε.

***************************************************************************************************
Για τον αριθμό των χαρακτήρων που αλλάζουν έχω κάνει define μια σταθερά στο αρχείο test_main.cpp***
***************************************************************************************************

----------------------------------------------Oject.h--------------------------------------------------------------:
ΚΛΑΣΣΕΙΣ:

Object:

-Αποτελείται από έναν protected ακέραιο αριθμό id, ο οποίος αυξάνεται κάθε φορά που δημιουργείται ένα αντικείμενο.
-Περιλαμβάνει και όλες τις συναρτήσεις που ζητούνται π.χ equal(), identical(), toString(),clone(),
όπως και τις συναρτήσεις setId(int) και getId() για την διαχείρηση του private μέλους του Object;
-Υπάρχει ένας constructor και ένας destructor για την δημιουργία και καταστροφή των αντικειμένων που δημιουργούνται.
Ο Constructor δέχεται ως όρισμα μια ακέραια μεταβλητή TOTAL_OBJECTS, η οποία είναι global και αυξάνεται κάθε φορά
με την δημιουργία αντικειμένων.
-equal(Object& obj) : Δέχεται αναφορά σε αντικείμενο και επιστρέφει true/false , this->id == obj.id
-identical(Object& obj): Ομοίως δέχεται αναφορά και συγκρίνει τη διεύθυνση του αντικειμένου με τον δείκτη this.
-toString(SString*) : Δέχεται κάθε φορά ένα αντικείμενο SString* και με την βοήθεια της concat(συνάρτηση της SString)
μετατρέπει το id σε SString και επιστρέφει μια συμβολοσειρά της μορφής [Object] [id] [αριθμός_αντ]
-getId() : Επιστρέφει το id
-setId(int) : Θέτει μια τιμή στο id
- clone() : Επιστρέφει δείκτη σε Object και είναι pure virtual.


SString:

-Αποτελείται από έναν δείκτη σε char.
-Κληρονομεί από την Object. Σε κάθε κλήση του Constructor του SString, γίνεται κλήση του Constructor του Object
-Γίνεται forward declaration έτσι ώστε η Object να μπορεί να δει την συμπεριφορά της.
-SString() : Default Constructor
-SString& operator=(const SString&) : Copy assignment operator
-SString(const SString&) : Copy constructor
-SString(int) : Μετατρέπει το int που δέχεται σε SString
-SString(const char*): Αρχικοποιεί το char* member του SString
-equal() : Καλεί την Object::equal() και στη συνέχεia με downcast ελέγχουμε αν τα data members των αντικειμένων είναι ίδια.
-identical() : Καλέι την Object identical
- clone() : Βάζω τον δείκτη this να δείχνει στο αντικέιμενο που θέλω να δημιουργήσω των κλώνο.
-print() : Εκτυπώνει το περιεχόμενο του char*.
- setString(const char*) / getString() : ...
- concat(const char*) : Κρατάω για αρχή σε μια προσωρινή μεταβλητή την τιμή του ήδη υπάρχοντος char* και στην ίδια μεταβλητή προσθέτω με την
strcat() την παράμετρό μου. Έπειτα διαγράφω το υπάρχουν str και δημιουργώ καινούριο χώρο αντιγράφοντας με την strcpy(str,προσωρινή_μετ).
-at(int) / length() / clear() / updateAt() : Η λειτουργικότητά τους βασίζεται στα ζητούμενα της άσκησης. Τίποτα το ιδιαίτερο να σημειωθεί.
- Υπάρχουν 3 διαφορετικές συναρτήσεις toString() .  Στην κλάσση αυτή χρησιμοποιώ κατά κύριο λόγο την toStrinng(SString*), όπου δέχεται ένα 
SString* , καλώ εσωτερικά την Object::toString(SString*) και στη συνέχεια με την χρήση της concat(), επαυξάνω το SString και επιστρέφω το
νέο SString που έχω δημιουργήσει.

-------------------------------------- PlaneApp.h -----------------------------------------------------------------------
ΚΛΑΣΣΕΙΣ:

PlaneComponent : 

-Κληρονομεί από την Object όλες τις συμπεριφορές της όπως equal(),identical(),clone(),toString().
- H clone(), έχω επιλέξει αν είναι pure virtual αφού δεν δημιουργούνται αντικείμενα της συγκεκριμένης κλάσσης.
- process(Employee&): Pure virtual. Δέχεται αναφορά σε εργαζόμενο. 
- ready_check(int): Pure virtual.
- toString(SString*) : Καλεί εσωτερικά την Object::toString(SString*) και επαυξάνω την παράμετρο με την χρήση της concat.
-PlaneComponent() / ~PlaneComponent(): Δεν υπάρχει κάτι ιδιαίτερο.

PassengerCompartment :

-Κληρονομέι από την PlaneComponent και έμμεσα από την Object.
- Περιέχει έναν δείκτη σε PassengerCompartment για την διαχείριση του "Εσωτερικού Χώρου", που είτε θα είναι NULL, είτε θα δείχνει κάπου.
- process(Employee&) : Κάνει override την PlaneComponent::process(Employee&). Στο εσωτερικό καλεί την workOn(PassengerCompartment&)
και αν υπάρχει εσωτερικός χώρος, τότε καλεί και γι αυτόν
- ready_check(int) : Overrides PlaneComponent::ready_check(int). Εμφανίζει μηνύματα.
- hasInside() : Επιστρέφει true ο δείκτης σε PassengerCompartment != NULL αλλιώς false.
- setInCompartment() / getInCOmp() : Settarei / παίρνει την τιμή του δείκτη.
- equal(), identical(), clone()...
- toString(SString*) , toString(SString*, int) : Καλεί εσωτερικά την PlaneComponent::toString(SString*) και έπειται διαμορφώνω το 
αποτέλεσμα με την χρήση της concat().
- PassengerCompartment() / ~PassengerCompartment() : Default Constructor / Destructor
- PassengerCompartment(const PassengerCompartment&) : Copy Constructor

PrivateCompartment :

- Κληρονομεί από την PlaneComponent
- Οι process() / ready_check() εδώ είναι pure virtual.
- Η toString(SString*) καλεί την PlaneComponent::toString(SString*) και ακολουθεί την ίδια λογική με τις προηγούμενες toString.
- equal(),identical(),clone() με την clone pure virtual.

********************************************************EquipmentCompartment, CargoBay*************************************************************
Οι EquipmentCompartment και CargoBay κληρονομόυν από την PrivateCompartment και επομένως όλες τις συμπεριφορές των PlaneComponent, Object.
Δεν νομίζω ότι υπάρχει κάτι ιδιαίτερο να αναφέρω, εκτός από το ότι η CargoBay έχει για data member, έναν δείκτη σε EquipmentCompartment, τον οποίο
δείκτη μπορώ και τον διαχειρίζομαι με setter/getters.  
**************************************************************************************************************************************************


Plane:

- Κληρονομεί από την Object.
- Για data member: 
	-int passCapacity ( χωριτηκότητα επιβατών ) /* Δίνεται στη γραμμή εντολών */
	-int nRooms ( χώροι επιβατών )		/* Δίνεται στη γραμμή εντολών */
	- SString* desc ( περιγραφή ) 
	- SString* plTitle ( τίτλος αεροπλάνου )
	- EquipmentCompartment *eqCompartment[3] ( Πίνακας από EquipmentComaprtment )
	- PassengerCompartment **room		( Πίνακας από PassengerCompartment )
- Επίσης κληρονομεί όλες τις συναρτήσεις του Object : equal(), identical(), toString(), clone()
- process(Employee&): Δέχεται έναν εργαζόμενο και για αυτόν τον εργαζόμενο καλεί την workOn.
- process(Employee **E) : Δέχεται έναν πίνακα εργαζομένων και για κάθε εργαζόμενο καλεί την process(Employee&)
ώστε να δουλέψει ο κάθε εργαζόμενος στο σωστό χώρο μέσα στο αεροπλάνο. Αφού δουλέψουν όλοι στους χώρους που πρέπει
καλείται η ready_check(), για κάθε ένα από τα μέλη του αεροπλάνου.
-  Υπάρχουν επίσης συναρτήσεις set/get για τα μέλη του αεροπλάνου.
- Η toString(SStrign*) καλεί την Object::toString(SString*) και στη συνέχεια καλείται η toString για κάθε ένα από τα
CargoBay, EquipmentCompartment, PassengerCompartment. Το τελικό αποτέλεσμα μας δίνει την δυνατότητα να γνωρίζουμε το id του 
κάθε αντικειμένου από αυτά , καθώς φαίνεται η ιεραρχία και η σειρά δημιουργίας των αντικειμένων. 


Employee:

- Κληρονομεί από την Object.
- Περιέχει έναν protected δείκτη σε SString , για το όνομα κάθε εργαζομένου.
- Υπάρχει η setString(const char*) και η getString() για την διαχείριση του data member.
- Υπάρχουν 4 συναρτήσεις workOn που είναι pure virtual:
	-workOn(Plane&)
	-workOn(PassengerCompartment&)
	-workOn(EquipmentCompartment&)
	-workOn(CargoBay)
- H report() είναι pure virtual.


********************************* SecurityEmployee, MaintenanceEmployee, CleaningEmployee ***************************************************
- Κληρονομούν όλες από την Employee.
-  Υπάρχουν Constructor / Destructor για την κάθε μία. Κατά την κλήση του Constructor, καλείται ο Consructor του Employee και κατ' επέκταση
ο Constructo του Object.
- Kληρονομόυν την setName(const char*) και getName() της Employee
- Υπάρχουν 4 workOn που κάνουν override τις workOn της Employee
- Η report() κάνει override την report της Employee
*********************************************************************************************************************************************

