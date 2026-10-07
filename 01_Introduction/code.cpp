// Music Playlist with Undo Skip
// Doubly Linked List + Stack
// C++
#include <iostream>
#include <string>
using namespace std;
struct Node
{
 string name;
 Node *prev;
 Node *next;
};
// Playlist pointers
Node *head = NULL;
Node *tail = NULL;
Node *cur = NULL;
// Stack for skipped songs
Node *skipped[5];
Node *oldPrev[5];
int top = -1;
// --------------------------------------------------
// ADD SONG
// --------------------------------------------------
void addSong()
{
 Node *s = new Node;
 cout << "Enter song name: ";
 cin >> s->name;
 s->prev = tail;
 s->next = NULL;
 if (head == NULL)
 {
 head = s;
 tail = s;
 cur = s;
 }
 else
 {
 tail->next = s;
 s->prev = tail;
 tail = s;
 }
 cout << "Song added successfully.\n";
}
// --------------------------------------------------
// NEXT SONG
// --------------------------------------------------
void nextSong() {
 if (cur == NULL)
 {
 cout << "Playlist is empty!\n";
 }
 else if (cur->next == NULL)
 {
 cout << "Already at the last song.\n";
 }
 else
 {
 cur = cur->next;
 cout << "Now playing: " << cur->name << endl;
 }
}
// --------------------------------------------------
// PREVIOUS SONG
// --------------------------------------------------
void previousSong()
{
 if (cur == NULL)
 {
 cout << "Playlist is empty!\n";
 }
 else if (cur->prev == NULL)
 {
 cout << "Already at the first song.\n";
 }
 else
 {
 cur = cur->prev;
 cout << "Now playing: " << cur->name << endl;
 }
}
// --------------------------------------------------
// SKIP CURRENT SONG
// --------------------------------------------------
void skipSong()
{
 if (cur == NULL)
 {
 cout << "Playlist is empty!\n";
 return;
 }
 Node *s;
 Node *p = s->prev;
 Node *n = s->next;
 // Remove current song from playlist
 if (p != NULL)
 p->next = n;
 else
 head = n;
 if (n != NULL)
 n->prev = p; else
 tail = p;
 // Stack is full
 if (top == 4)
 {
 // Remove oldest skipped song from stack.
 // Do NOT delete the node here because it may
 // still be needed by playlist/undo logic.
 for (int i = 0; i < 4; i++)
 {
 skipped[i] = skipped[i + 1];
 oldPrev[i] = oldPrev[i + 1];
 }
 top = 3;
 }
 // Push skipped song into stack
 top++;
 skipped[top] = s;
 oldPrev[top] = p;
 // Disconnect skipped node from playlist
 s->prev = NULL;
 s->next = NULL;
 // Select next song, otherwise previous song
 if (n != NULL)
 cur = n;
 else
 cur = p;
 cout << "Skipped: " << s->name << endl;
 if (cur != NULL)
 cout << "Now playing: " << cur->name << endl;
 else
 cout << "No songs remaining in playlist.\n";
}
// --------------------------------------------------
// UNDO SKIP
// --------------------------------------------------
void undoSkip()
{
 if (top == -1)
 {
 cout << "Nothing to undo!\n";
 return;
 }
 Node *s = skipped[top];
 Node *p = oldPrev[top];
 // Remove from stack
 top--;
 Node *n; // Find the song that should come after s
 if (p != NULL)
 n = p->next;
 else
 n = head;
 // Insert skipped song back
 s->prev = p;
 s->next = n;
 if (p != NULL)
 p->next = s;
 else
 head = s;
 if (n != NULL)
 n->prev = s;
 else
 tail = s;
 // Make restored song current
 cur = s;
 cout << "Undo successful.\n";
 cout << "Restored song: " << s->name << endl;
}
// --------------------------------------------------
// SHOW PLAYLIST
// --------------------------------------------------
void show()
{
 cout << "\n-----------------------------\n";
 cout << " MUSIC PLAYLIST\n";
 cout << "-----------------------------\n";
 if (head == NULL)
 {
 cout << "Playlist is empty.\n";
 cout << "-----------------------------\n";
 return;
 }
 Node *t = head;
 while (t != NULL)
 {
 cout << t->name;
 if (t == cur)
 cout << " <-- PLAYING";
 cout << endl;
 t = t->next;
 }
 cout << "-----------------------------\n";
} // --------------------------------------------------
// DELETE ALL SONGS
// --------------------------------------------------
void cleanup()
{
 Node *temp = head;
 while (temp != NULL)
 {
 Node *nextNode = temp->next;
 delete temp;
 temp = nextNode;
 }
 head = NULL;
 tail = NULL;
 cur = NULL;
 // Clear stack references
 for (int i = 0; i < 5; i++)
 {
 skipped[i] = NULL;
 oldPrev[i] = NULL;
 }
 top = -1;
}
// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main()
{
 int c;
 do
 {
 cout << "\n=================================\n";
 cout << " MUSIC PLAYLIST SYSTEM\n";
 cout << "=================================\n";
 cout << "1. Add Song\n";
 cout << "2. Next Song\n";
 cout << "3. Previous Song\n";
 cout << "4. Skip Song\n";
 cout << "5. Undo Skip\n";
 cout << "6. Show Playlist\n";
 cout << "0. Exit\n";
 cout << "=================================\n";
 cout << "Enter your choice: ";
 cin >> c;
 switch (c)
 {
 case 1:
 addSong();
 show();
 break; case 2:
 nextSong();
 show();
 break;
 case 3:
 previousSong();
 show();
 break;
 case 4:
 skipSong();
 show();
 break;
 case 5:
 undoSkip();
 show();
 break;
 case 6:
 show();
 break;
 case 0:
 cout << "Exiting program...\n";
 break;
 default:
 cout << "Invalid choice! Please try again.\n";
 }
 } while (c != 0);
 cleanup();
 return 0;
}