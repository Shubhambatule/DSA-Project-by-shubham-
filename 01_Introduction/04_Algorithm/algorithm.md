3.	Algorithm
1.	Start the program.
2.	Initialize head, tail, current, and the skip stack as empty.
3.	Display the menu containing the options: Add, Next, Previous, Skip, Undo, Display, and Exit.
4.	Read the user's choice and validate the input. If the choice is invalid, ask the user to enter a valid choice again.
5.	Add Song: Create a new song node. If the list is empty, make the new node the head, tail, and current node. Otherwise, attach the new node after the tail and update the tail pointer.
6.	Play Next: Check whether current->next exists. If it exists, move current to the next node. Otherwise, display the message "End of playlist".
7.	Play Previous: Check whether current->prev exists. If it exists, move current to the previous node. Otherwise, display the message "Already at first song".
8.	Skip Song: Store p = current->prev and n = current->next. Relink the surrounding nodes by setting p->next = n and n->prev = p. If p is NULL, update head to n. If n is NULL, update tail to p. Push the skipped song and p onto the skip-history stack. If the stack contains more than five records, remove the oldest record. Move current to n if n exists; otherwise move current to p.
9.	Undo Skip: Check whether the skip stack is empty. If it is empty, display a suitable message. Otherwise, pop the most recent skip record. Find n = p->next when p is not NULL; if p is NULL, use the current head as n. Relink the skipped song between p and n. Update head or tail if required, and make the restored song the current song.
10.	Display Playlist: Traverse the doubly linked list from head to tail and print every song. Mark the current song to indicate which song is currently playing.
11.	Repeat the menu and corresponding operations until the user chooses the Exit option.
12.	Stop the program
