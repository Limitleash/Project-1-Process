#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//butuh file processing untuk edit nodenya
struct TimeS
{
   char day[40];
   char time[20];
   char date[13];
   char month[13];
   char year[13];
};

struct comment_like
{
   char comment[260];
   char get_time[260];
   unsigned long long int like;
   TimeS x;
   comment_like *next,*prev;
};

struct binTrash
{
   char temp[260][260];
   char validate;
   binTrash *next,*prev;
};

struct Notes
{
   char Note[1000];//since note can taken a paragraph
   TimeS now;
   comment_like *head,*tail;//harena setiap node ada link list comment_likenya
   Notes *next,*prev;//for make a link list notes
};

struct message
{
   char word[260];
};

struct Send_Request
{

};

struct Inbox
{

};

struct FriendInbox{ //Sebagai tempat message ketika ada yang request friend ke user
   char username[24+1];
   FriendInbox *next_inbox, *previous_inbox;
};

struct FriendRequested{ //Sebagai tempat message user me-request friend ke siapa saja
   char username[24+1];
   FriendRequested *next_requested, *previous_requested;
};

struct FriendList{ //Sebagai Database daftar teman User
   char username[24+1];
   FriendList *next_friend, *previous_friend;
};

struct UserList //sebagai Database daftar User te-registrasi
{
   char username[260]; //Bukannya 24 ya paling panjang length-nya?
   char password[260]; //Bukannya 24 ya paling panjang length-nya?
   FriendInbox friend_inbox; //tiap user ada database friend inbox, friend requested, dan friend list nya tersendiri
   FriendRequested friend_requested; //struct-nya dihilangkan juga gpp (pake .cpp soalnya)
   FriendList friend_list;
   UserList *next_user, *previous_user; //next user untuk ke user selanjutnya di daftar user
   Notes *headback, *tailback;
   Notes *headprog,*tailprog;
   Notes *headreview,*tailreview;
   Notes *headblock,*tailblock;
   Notes*headone,*taildone;
   Notes*headtest,*tailtest;
   binTrash *test1, *test2;
};


Notes*makeNotes(const char*note)
{
   Notes*curr = (Notes*)malloc(sizeof(Notes));

   strcpy(curr->Note,note);

   struct tm*local;
   time_t nowtime;
   char temp[90][200]={};
      // strcpy(temp,);
      char sp[30]={};
      strcpy(sp,ctime(&nowtime));
      char*toku;
      toku = strtok(sp," ");
      int y = 0;
// string format Sun Jan 17 22:02:53 2021
      while(toku!=NULL)
      {
         strcpy(temp[y],toku);
         toku= strtok(NULL," ");
         y++;
      }
      strcpy(curr->now.year,temp[4]);
      strcpy(curr->now.month,temp[1]);
      strcpy(curr->now.day,temp[0]);
      strcpy(curr->now.time,temp[3]);
      strcpy(curr->now.date,temp[2]);
   curr->next=curr->prev=NULL;

   return curr;
}

void show_users(UserList **first, UserList **last){ //menampilkan semua user yang telah te-registrasi
   UserList *current = *first;
   int number = 1;
   while(current != NULL){
      printf("%-3d %s\n", number++, current->username);
      current = current->next_user;
   }
   // UserList *current = *last;
   // while(current != NULL){
   //     printf("%s\n", current->username);
   //     current = current->previous_user;
   // }
   puts(""); //Debug
}

UserList *createNew(const char *username, const char *password){ //buat user baru
   UserList *newUser = (UserList *) malloc(sizeof(UserList));
   strcpy(newUser->username, username); //inisialisasi username dan password
   strcpy(newUser->password, password);
   newUser->next_user = newUser->previous_user = NULL; //semua pointer yang ada di user baru diarahkan ke NULL

   strcpy(newUser->friend_inbox.username, username);
   newUser->friend_inbox.next_inbox = newUser->friend_inbox.previous_inbox = NULL;
   strcpy(newUser->friend_requested.username, username);
   newUser->friend_requested.next_requested = newUser->friend_requested.previous_requested = NULL;
   strcpy(newUser->friend_list.username, username);
   newUser->friend_list.next_friend = newUser->friend_list.previous_friend = NULL;
   newUser->headback=newUser->tailback=newUser->headblock=newUser->tailblock=NULL;
   newUser->headone=newUser->taildone=newUser->headprog=newUser->tailprog=NULL;
   newUser->headreview=newUser->tailreview=newUser->headtest=newUser->tailtest=NULL;
   newUser->test1=newUser->test2=NULL;

   return newUser;
}
void times_get(UserList **logged_user)
{
   struct tm*local;
   time_t nowtime;
   printf("Logged in: %s\n",ctime(&nowtime));
}


comment_like*makecomment(unsigned long long int like,const char *comment)
{
   comment_like*currNote=(comment_like*)malloc(sizeof(comment_like));

   strcpy(currNote->comment,comment);
   currNote->like=like;


   struct tm*local;
   time_t nowtime;
   char temp[90][200]={};
      // strcpy(temp,);
      char sp[30]={};
      strcpy(sp,ctime(&nowtime));
      char*toku;
      toku = strtok(sp," ");
      int y = 0;
// string format Sun Jan 17 22:02:53 2021
      while(toku!=NULL)
      {
         strcpy(temp[y],toku);
         toku= strtok(NULL," ");
         y++;
      }
      strcpy(currNote->x.year,temp[4]);
      strcpy(currNote->x.month,temp[1]);
      strcpy(currNote->x.day,temp[0]);
      strcpy(currNote->x.time,temp[3]);
      strcpy(currNote->x.date,temp[2]);
      currNote->next=currNote->prev=NULL;

   return currNote;
}

void register_user(UserList **first, UserList **last, char username[], char password[]){
   // puts("Berhasil register1"); //Debug
   UserList *newUser = createNew(username, password);
   // puts("Berhasil register2"); //Debug
   if((*first) == NULL){ //Jika belum ada user te-registrasi (first masi mengarah ke NULL)
      // puts("Berhasil register if1"); //Debug
      (*first) = (*last) = newUser;
   }
   else if(strcmp(username, (**first).username) < 0){ //pushHead
      // puts("Berhasil register if2"); //Debug
      newUser->next_user = (*first);
      (*first)->previous_user = newUser;
      (*first) = newUser;
   }
   else if(strcmp(username, (**last).username) > 0){ //pushTail
      // puts("Berhasil register if3"); //Debug
      (**last).next_user = newUser;
      newUser->previous_user = (*last);
      (*last) = newUser;
   }
   else{ //pushMid
      // puts("Berhasil register if4"); //Debug
      UserList *current = (*first);
      while(current != NULL){
         if(strcmp(current->username, username) >= 0){
               break;
         }
         else{
               current = current->next_user;
         }
      }
      // printf("current: %s\n", current->username); //Debug

      // show_users(first, last); //Debug

      // printf("newUser->previous_user: %s\n", current->previous_user); //Debug
      newUser->previous_user = current->previous_user;
      // printf("newUser->next_user: %s\n", current->username); //Debug
      newUser->next_user = current;
      // printf("current->previous_user: %s\n", newUser->username); //Debug
      current->previous_user = newUser;
      // printf("newUser->previous_user->next_user: %s\n", newUser->username); //Debug
      newUser->previous_user->next_user = newUser;
   }
}

//untuk mengecek apakah username dan password sudah benar atau belum
char get_login(const char *temp_name, const char *temp_pass, UserList **first, UserList **logged_user){
   UserList *current = (*first);
   while(current != NULL){ //Jika current-nya NULL, berarti user belum te-registrasi
      if(strcmp(current->username, temp_name) < 0){
         current = current->next_user;
      }
      else if(strcmp(current->username, temp_name) == 0){ //Jika dapat username yang sesuai
         if(strcmp(current->password, temp_pass) == 0){ //Jika password benar
            // puts("berhasil"); //Debug
            (*logged_user) = current;
            return '0';
         }
         else{ //Jika password salah
            puts("\nUsername or Password is wrong!");
            return '1';
         }
      }
      else{ //Username belum te-registrasi
         puts("\nUsername didn't exist!");
         return '1';
      }
   }
   if(current == NULL){
      puts("\nUsername didn't exist!");
      return '1';
   }
}

void show_friend(UserList **logged_user){ //untuk menampilkan semua teman User
   FriendList *current = (**logged_user).friend_list.next_friend;
   int number = 1;
   while(current != NULL){
      printf("%-3d %s\n", number++, current->username);
      current = current->next_friend;
   }
}

void pusHeadBack(UserList**logged_user,const char * noty)
{
   UserList*backlog=makeNotes(noty);
   if()
}
void make_note(UserList**logged_user)
{
   puts("Welcome to notes pages :>");
   puts("Enter a note");
   puts("For saving purpose click enter+tab and then enter again");

   char tempn[1000]={};
   scanf("%[^\t]",tempn);
   getchar();
   char category;
   puts("Now choose where do you want to store this note");
   puts("[1] Backlog");
   puts("[2] In Progress");
   puts("[3] Peer review");
   puts("[4] In Test");
   puts("[5] DoneNote");
   puts("[6] Blocked");

   while(category>'6'||category<'1')
   {
      scanf("%c",&category);
   }
   if(category=='1')
   {
      pusHeadBack(logged_user,tempn);
   }
}
void login_menu(UserList **logged_user){
   for(;;){ //Menu setelah User berhasil login
   system("CLS || clear");
   puts("Oo=====================================oO");
   printf("Welcome Back, %s!\n", (*logged_user)->username);
   puts("Oo=====================================oO");
   times_get(logged_user);
   puts("------------------------\n");

   printf("[All Friends of %s]\n", (**logged_user).username);
   puts("No.  Username");
   show_friend(logged_user);

   puts("\n------------------------");
   puts("       >> Menu <<         ");
   puts("------------------------");
   puts("[1] Add Friend");
   puts("[2] Remove Friend");
   puts("[3] View Inbox");
   puts("[4] View Sent Request");
   puts("[5] Add / Edit / Announce / Delete Note");
   puts("[6] Log out");
   puts("------------------------");
   char use = '\0';
   while(use<'1' || use>'6')
   {
      printf(">> ");
      scanf("%c",&use);
      getchar();
   }
   switch(use){
      case '1':
         // puts("[1] Add Friend");
         break;

      case '2':
         // puts("[2] Remove Friend");
         break;

      case '3':
         // puts("[3] View Inbox");
         break;

      case '4':
         // puts("[4] View Sent Request");
         break;

      case '5':
         // puts("[5] Add / Edit / Announce / Delete Note");
         break;

      case '6':
         // puts("[6] Log out");
         return;

      default: //Debug
         printf("[PROBLEM IN CODE]");
   }

}
}

void menu(UserList **first, UserList **last) //Menu awal ketika program baru berjalan
{for(;;){
   system("CLS || clear");
   puts("Oo=====================================oO");
   puts("               STUDY NETWORK             ");
   puts("Oo=====================================oO\n");
   puts("[All User]\n");
   show_users(first, last);
   puts("------------------------");
   puts("[1] Register");
   puts("[2] Login");
   puts("[3] Exit");
   puts("------------------------");
   puts("------------------------");
   puts("Press 0 and enter to abort an operation");
   puts("------------------------");
   char use = '\0';
   while(use<'0'||use>'3')
   {
      printf(">> ");
      scanf("%c",&use);
      getchar();
   }

   if(use=='0')
   {
      // puts("back to main menu");
      menu(first, last);
   }
   else if (use=='1') //BELUM ADA VALIDASI REGISTER
   {
      char name[24+1], pass[24+1];
      puts("make account in progress");
      printf("Username: ");
      scanf("%[^\n]", name);
      getchar();
      printf("Password: ");
      scanf("%[^\n]", pass);
      getchar();
      register_user(first, last, name, pass);
   }
   else if (use=='2')
   {
      puts("------------------------");
      printf("Username: ");
      char temp_name[24+1], temp_pass[24+1];
      scanf("%[^\n]", temp_name);
      getchar();
      printf("Password: ");
      scanf("%[^\n]", temp_pass);
      getchar();

      UserList *logged_user; //Sebagai penanda "user yang login" di dalam "daftar user"
      char flag = get_login(temp_name, temp_pass, first, &logged_user); //cek username dan pass (Validasi)
      if(flag == '0'){ //login sukses
         puts("\n--- Login Successfull ---");
         printf("Press Enter to Continue...");
         getchar();
         login_menu(&logged_user); //masuk ke menu login
      }
      else if(flag == '1'){ //login gagal
         // puts("else if '1' login"); //Debug
         printf("Press Enter to Continue...");
         getchar();
         continue; //kembali ke awal
      }
      else{ //Jika masuk kesini, berarti ada kesalahan dalam coding
         puts("[PROBLEM IN CODE]"); //Debug
         printf("Press Enter to Continue...");
         getchar();
         continue; //kembali ke awal
      }
   }
   else if (use=='3') //Program berakhir
   {
      system("cls||clear");
      return; //keluar dari modul menu
      // puts("we gonna exit this app");
   }

   // printf("YOU MADE A MAIN MENU !! :>");

}

}

int main(){
   UserList *first = NULL; //first paling kiri/awal, last paling kanan/akhir
   UserList *last = NULL; //User List diurutkan sesuai namanya. Contohnya first di inisial A, sedangkan last di inisial Z
   menu(&first, &last);
   return 0;
}