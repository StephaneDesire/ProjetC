
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherMenu() {
    printf("\n\n\n\n");
    printf("                         Menu\n");
    printf("                1. Ajouter une voiture\n");
    printf("                2. Louer une voiture\n");
    printf("                3.Afficher les caracteristiques d'une voiture\n");
    printf("                4. Creer un profil client\n");
    printf("                5. Modifier les caracteristiques d'une voiture\n");
    printf("                6. Retirer une voiture en panne\n");
    printf("                7. Retourner une voiture\n");
    printf("                8. Afficher l'historique de location \n");
    printf("                9. Afficher la voiture la plus louee\n");
    printf("                10. Afficher tous les clients de l'agence\n");
    printf("                11. Afficher un client\n");
    printf("                12. Trouver une voiture \n");
    printf("                13. Retirer un client de la liste des client \n");
    printf("                14. Supprimer une location \n");
    printf("                15. Afficher toutes les voitures de l'agence \n");
    printf("                16. Quitter\n");
}



//Création d'une structure voiture

typedef struct Car {
    int id;
    char*immatriculation;
    char marque[100];
    char model[100];
    char color[100];
    int year;
    int isAvailable;
    int locationId;
} Car;

Car* carList[100];
int carCount = 0;
int locationCount = 0;
int clientCount=0;


//Creation d'une voiture
Car* createCar() {int id;char immatriculation[100]; char marque[100];char model[100];char color[100];int year; int isAvailable;

Car* newCar = (Car*) malloc(sizeof(Car));
printf("               \n\t\t Veuillez saisir l'identifiant de la voiture : ");
scanf("%d",&id);
printf("                \n\t\tVeuillez entrer l'immatriculation de la voiture : ");
scanf("%s",newCar->immatriculation);
printf("                \n\t\t Veuillez saisir la marque : ");
scanf("%s",newCar->marque);
printf("                \n\t\tVeuillez saisir le modele de la voiture :");
scanf("%s",newCar->model);
printf("                 \n\t\tVeuillez saisir la couleur de la voiture :");
scanf("%s",newCar->color);
printf("                 \n\t\tVeuillez saisir l'anne de la voiture :");
scanf("%d",&year);
printf("                 \n\t\tVeuillez dire si la voiture est disponible ou pas:");
scanf("%d",&isAvailable);
newCar->id = id;
strcpy(newCar->immatriculation,immatriculation);
strcpy(newCar->marque,marque);
strcpy(newCar->model,model);
strcpy(newCar->color,color);
newCar->year=year;
newCar->isAvailable = isAvailable;
newCar->locationId = -1;
return newCar;
}
//Affiche les caracteristiques d'une voiture entree en parametre
void printCar(Car* car) {
    printf("Car ID: %d\n", car->id);
    printf("immatriculation: %s\n",car->immatriculation);
    printf("marque: %s\n", car->marque);
    printf("model: %s\n", car->model);
    printf("year: %d\n", car->year);
    printf("Available: %s\n", car->isAvailable ? "Yes" : "No");
    if (car->locationId != -1) {
        printf("Location ID: %d\n", car->locationId);
    }
}



//Enregistrement de la voiture dans la base de donnees
void saveCar(Car *car){
FILE*file=fopen("cars.bin","ab");
if (!file){
    printf("Erreur lors de la creation du fichier binaire.\n");
    return;
}
fwrite(car,sizeof(Car),1,file);
fclose(file);
}

void displayCar(Car* car){
printf("ID:%d\n",car->id);
printf("Immatriculation:%s\n",car->immatriculation);
printf("Marque:%s\n",car->marque);
printf("Model:%s\n",car->model);
printf("Color:%s\n",car->color);
printf("Year:%d\n",car->year);
printf("IsAvailable:%d\n",car->isAvailable);
printf("Location:%d\n",car->locationId);

}

//Afficher toutes les voitures de l'agence
void afficherCar(){
FILE *file=fopen("cars.bin","rb");
if(file==NULL){
    printf("Erreur lors de l'ouverture du fichier binaire.\n");
    exit(0);
}
Car *car;
while(fread(&car,sizeof(Car),1,file)==1){
    displayCar(car);
}
fclose(file);
}

// La nouvelle voiture sera enregistrée dans le tableau qui represente l'ensemble des voitures de la societe
void addCar(Car* car) {
    carList[carCount++] = car;

}

void modifierVoiture(Car **carList) {
    int id;

    printf("\n\t\t Veuillez entrer l'identifiant de la voiture a modifier: ");
    scanf("%d", &id);

    Car *car = carList;
    while (car != NULL) {
        if (car->id =id) {
           printf("Entrez la nouvelle disponibilite de la voiture (1 - Disponible, 0 - Indisponible): ");
            scanf("%d", &car->isAvailable);

            printf("La voiture a ete modifiee avec succes.\n");
            return;
        }
    }

    printf("Aucune voiture correspondante a ete trouvee.\n");
}





void supprimerVoiture(Car **carList, int taille) {
    int id;
    printf("\n\t\tVeuillez saisir l'identifiant de la voiture a supprimer:");
    scanf("%d",&id);
    int i, j;
    for (i = 0; i < taille; i++) {
            char id_str[20];
    sprintf(id_str,"%d",id);
    if(i==taille -1){
        printf("Aucune voiture triuvee sous ce numero");
        break;
    }
        if (strcmp((*carList)[i].id, id_str) == 0) {

            for (j = i; j < taille - 1; j++) {
        (*carList)[j] = (*carList)[j + 1];
    }




    /*if (i == *taille) {
        printf("Aucune voiture de ce numero %s trouvée\n", id);
        return;*/
    }

   /* for (j = i; j < *taille - 1; j++) {
        (carList)[j] = (carList)[j + 1];
    }*/

    (taille)--;
    break;


   carList = realloc(carList, sizeof(Car) * (taille));
        }

        }

Car *retournerVoiture( Car **carList, int *taille) {
    int i;
    int id;
    printf("\n\t\tVeuillez saisir l'identifiant de la vous que vous souhaitez retournerure ");
    scanf("%d",&id);
    for (i = 0; i < *taille; i++) {
        if (strcmp((*carList)[i].id, id) == 0) {
            break;
        }
    }

    if (i == *taille) {
        printf("Aucune voiture enregistrée sous ce numero trouvee trouvée\n", id);
        return NULL;
    }



Car *voitureRetournee = malloc(sizeof(Car));
    strcpy(voitureRetournee->id, (*carList)[i].id);
    voitureRetournee->year= (*carList)[i].year;

    for (int j = i; j < *taille - 1; j++) {
        (*carList)[j] = (*carList)[j + 1];
    }

    (*taille)--;
    *carList = realloc(*carList, sizeof(Car) * (*taille));

    return voitureRetournee;
}





//Creation d'une structure client
typedef struct Client {
    int idt;
    int ncin;
    char familyName[100];
    char firstName[100];
    int yearOld;

} Client;

Client*clientList[100];

//Creation  d'un profil client
Client *createClient() {int idt;int ncin;char familyName[20];char firstName[20];int yearOld;
printf("\n\t\tVeuillez saisir l'identifiant du client:");
scanf("%d",&idt);
printf("\n\t\tVeuillez entrer le numero de sa carte d'identite nationale ou du passeport : ");
scanf("%d",&ncin);
printf("\n\t\tVeuillez saisir le  nom de Famille du client :");
scanf("%s",familyName);
printf("\n\t\tVeuillez saisir le prenom du client :");
scanf("%s",firstName);
do{
printf("\n\t\tVeuillez saisir l'age du client :");
scanf("%d",&yearOld);
printf("\n\t\tVous ne pouvez louer un voiture si vous n'etes majeur,Merci");}
while (yearOld<18);
// un individu non majeur ne peut etre client
Client* newClient = (Client*) malloc(sizeof(Client));
newClient->idt= idt;
strcpy(newClient->familyName,familyName);
strcpy(newClient->firstName,firstName);
newClient->yearOld=yearOld;
return newClient;

}

//Affiche les caracteristiques d'un client entre en parametre
void printClient(Client* client) {
    printf("Client ID: %d\n", client->idt);
    printf("ncin: %d\n",client->ncin);
    printf("familyName: %s\n", client->familyName);
    printf("firstName: %s\n", client->firstName);
    printf("Age: %d\n", client->yearOld);

}



//Enregristrement du cleint dans la base de donnes qui n'est rien d'autre qu'un fichier binaire

void enregistrerClient(Client *client){
FILE*fichier=fopen("clients.bin","ab");
if(!fichier){
    printf("Erreur lors de l'ouverture du fichier.\n");
    return;
}
fwrite(client,sizeof(Client),1,fichier);
fclose(fichier);}


void afficherClients(){
FILE*fichier=fopen("clients.bin","rb");
if(!fichier){
        printf("Erreur lors de l'ouverture du fichier.\n");
return;

}
Client *client;
while(fread(client,sizeof(Client),1,fichier)){
    printf("ID: %d\n",client->idt);
    printf("Ncin: %d\n",client->ncin);
    printf("Nom: %s\n",client->familyName);
    printf("Prenom: %s\n",client->firstName);
    printf("Age: %d\n",client->yearOld);
    printf("\n");

}
fclose(fichier);
}


//Creation d'un tableau de clients et ajout de nouveaux clients
void addClient(Client* client) {
    clientList[clientCount++] = client;}

void retirerClient(Client **clientList, int *taille) {
    int idt;
    printf("\n\t\tVeuillez saisir l'identifiant du client a retirer:");
    scanf("%d",&idt);
    int i, j;
    for (i = 0; i < *taille; i++) {
        if (strcmp((*clientList)[i].idt, idt) == 0) {
            break;
        }
    }

    if (i == *taille) {
        printf("Aucun client enregistre sous ce numero %s trouvé\n", idt);
        return;
    }

    for (j = i; j < *taille - 1; j++) {
        (*clientList)[j] = (*clientList)[j + 1];
    }

    (*taille)--;
    *clientList = realloc(*clientList, sizeof(Client) * (*taille));
}




//Création d'une structure location
typedef struct Location {
    int id;//Numero de location
    int carId;//l'identifiant de la voiture louée
    //Dans un souci de clarté la date de location a été subdivisée en jour mois et année
    int clientIdt;//identifiant du client qui loue la voiture
    int startDay;
    int startMonth;
    int startYear;
    int endDay;
    int endMonth;
    int endYear;
} Location;

Location* locationList[100];


//La fonction suivante permettra de louer une nouvelle voiture
Location* createLocation(){int id;int carId;int clientIdt; int startDay; int startMonth;int startYear;int endDay;int endMonth;int endYear;


    printf("Veuillez saisir l'identifiant de Location : ");
    scanf("%d",&id);
    printf("Veuillez saisir l'identifiant de la voiture louee :");
    scanf("%d",&carId);
    printf("Veuillez saisir l'identifiant du client qui loue la voiture :");
    scanf("%d",&clientIdt);
    do{
    printf("Veuillez saisir le jour de location,le mois de location et l'anne de location:");
    scanf("%d%d%d",&startDay,&startMonth,&startYear);}
    while(startDay>31 || startMonth>12);
    //S'assurer de ne pas depasser le nombre de jour du mois ou le nombre de mois dans l'annee
    printf(" La date de retour ne peut etre anterieure a la date de location");
    printf("Veuillez entrer le jour,le mois et l'annee de retour de la voiture louee :");
    scanf("%d%d%d",&endDay,&endMonth,&endYear);

    Location* newLocation = (Location*) malloc(sizeof(Location));
    newLocation->id = id;
    newLocation->carId = carId;
    newLocation->clientIdt=clientIdt;
    newLocation->startDay = startDay;
    newLocation->startMonth = startMonth;
    newLocation->startYear=startYear;
    newLocation->endDay = endDay;
    newLocation->endMonth = endMonth;
    newLocation->endYear=endYear;
    return newLocation;
}
//Enregristrement d'une location dans la base de donnes qui n'est rien d'autre qu'un fichier binaire

void enregistrerLocation(Location *location){
FILE*fichier=fopen("locations.bin","ab");
if(!fichier){
    printf("Erreur lors de l'ouverture du fichier.\n");
    return;
}
fwrite(location,sizeof(Location),1,fichier);
fclose(fichier);}


void afficherLocation(){
FILE*fichier=fopen("locations.bin","rb");
if(!fichier){
        printf("Erreur lors de l'ouverture du fichier.\n");
return;

}
Location *location;
while(fread(location,sizeof(Location),1,fichier)){
    printf("Identifiant de location: %d\n",location->id);
    printf("Identifiant de la voiture louee: %d\n",location->carId);
    printf("Identifiant du client : %d\n",location->clientIdt);
    printf("Jour:\n Mois:\n Annee:\n %s%s%s\n",location->startDay,location->startMonth,location->startYear);
    printf("Jour:\n Mois:\n Annee:\n %s%s%s\n",location->endDay,location->endMonth,location->endYear);
    printf("\n");

}
fclose(fichier);
}



void supprimerLocation(Location **locationList, int *taille) {
    int id;
    printf("\n\t\tVeuillez saisir l'identifiant de la location a retirer:");
    scanf("%d",&id);
    int i, j;
    for (i = 0; i < *taille; i++) {
        if (strcmp((*locationList)[i].id, id) == 0) {
            break;
           /* if (i == *taille) {
        printf("Aucune location enregistre sous ce numero %d trouvé\n", id);
        return;


    }*/

     /*for (j = i; j < *taille - 1; j++) {
        (*locationList)[j] = (*locationList)[j + 1];
    }*/

        }
    }

   if (i == *taille) {
        printf("Aucune location enregistre sous ce numero %s trouvé\n", id);
        return;
    }

    for (j = i; j < *taille - 1; j++) {
        (*locationList)[j] = (*locationList)[j + 1];
    }

    (*taille)--;
    *locationList = realloc(*locationList, sizeof(Location) * (*taille));
}







void printCarHistory(Location *locations, int locationCount) {
    int i;

    for (i = 0; i < locationCount; i++) {
        Location location = locations[i];
        printf("Location ID: %d\n", location.id);
        printf("Car ID: %d\n", location.carId);
        printf("Client ID: %d\n", location.clientIdt);
        printf("Start Date: %d/%d/%d\n", location.startDay, location.startMonth, location.startYear);
        printf("End Date: %d/%d/%d\n", location.endDay, location.endMonth, location.endYear);
        printf("\n");
    }
}


//Trouver les voitures les plus louees
void findMostRentedCar(Location *locations, int locationCount) {
    int i;
    int *carCounts = (int *)calloc(locationCount, sizeof(int));

    for (i = 0; i < locationCount; i++) {
        carCounts[locations[i].carId]++;
    }

    int maxCount = 0;
    int mostRentedCarId = -1;

    for (i = 0; i < locationCount; i++) {
        if (carCounts[i] > maxCount) {
            maxCount = carCounts[i];
            mostRentedCarId = i;
        }
    }

    if (mostRentedCarId != -1) {
        printf("\n\t\tThe most rented car ID is: %d\n", mostRentedCarId);
    } else {
        printf("No car was rented.\n");
    }

    free(carCounts);
}



//Cette fonction permettra de conserver l'historique des locations
void addLocation(Location* location) {
    locationList[locationCount++] = location;
}
//Les fonctions findcarById et findlocationById permettront au gerant de la societe de retrouver une voiture dans son garage et de voir si celle ci a été louée ou pas
Car* findCarById(int id) {
    for (int i = 0; i < carCount; i++) {
        if (carList[i]->id == id) {
            return carList[i];
        }
        else
            printf("Aucune voirure trouvee sous ce numero");
    }
    return NULL;
}

Location* findLocationById(int id) {
    for (int i = 0; i < locationCount; i++) {
        if (locationList[i]->id == id) {
            return locationList[i];
        }
        else
            printf("Aucune location trouvee sous ce numero");
    }
    return NULL;
}



void printLocation(Location* location) {
    printf("Location ID: %d\n", location->id);
    printf("Car ID: %d\n", location->carId);
    printf("Start Day: %d\n", location->startDay);
    printf("Start Month: %d\n", location->startMonth);
    printf("Start Year: %d\n", location->startYear);
    printf("End Day: %d\n", location->endDay);
    printf("End Month: %d\n", location->endMonth);
    printf("End Year: %d\n", location->endYear);


}

int main() {
     int choix;

   do {
        afficherMenu();
        printf("                        ***********************************\n");
        printf("                         Veuillez entrer votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:{
                Car*car2=createCar();
                addCar(car2);
                saveCar(car2);}
                break;
            case 2:{
              Location* location1= createLocation();
                addLocation(location1);
                enregistrerLocation(location1);}
                break;
             case 3:{
               // afficherCaracteristiques(car_list);
                 for (int i = 0; i < carCount; i++) {
        printCar(carList[i]);
    }}
                break;
            case 4:{
                Client *client1 = createClient();
                addClient(client1);
                enregistrerClient(client1);}
                break;
            case 5:
                 modifierVoiture(carList);
                break;
            case 6:
                supprimerVoiture(*carList,20);
                break;
            case 7:
                retournerVoiture(carList,20);
                break;
            case 8:{
              printCarHistory(locationList,20);}
                break;
            case 9:{
               findMostRentedCar(locationList,20);}
               break;
            case 10:{
               afficherClients();}
               break;

             case 11:{
                 Client *client;
               printClient(client);}
               break;
             case 12:{
                 int id;
                 printf("\n\t\tVeuillez saisir l'identifiant de la fiche de location");
                 scanf("%d",&id);
                 findLocationById(id);}
               break;
            case 13:{
            retirerClient(clientList,20);
            break;}
            case 14:{
            supprimerLocation(locationList,20);
            break;}

           case 15:{
            afficherCar();
            break;}

            default:
                printf("\n\t\tChoix incorrect.\n");
        }
    } while (choix != 15);




 /*   // Create and add cars
    Car* car1 = createCar();
    addCar(car1);

    // Create and add locations
    Location* location1 = createLocation();
    Location* location2 = createLocation();
    addLocation(location1);
    addLocation(location2);


    // Print cars
    for (int i = 0; i < carCount; i++) {
        printCar(carList[i]);
    }

    // Print locations
    for (int i = 0; i < locationCount; i++) {
        printLocation(locationList[i]);
    }*/

    return 0;
}
