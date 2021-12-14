# Event_System
A single-header, self-managing system for creating events in C++

Events can contain pointers to Event Listeners of the corresponding type.
Event Listeners will automatically remove themselves from any events they listen to when they are destroyed
