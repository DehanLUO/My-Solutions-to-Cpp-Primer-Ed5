/*
 * Exercise 13.36: Design and implement the corresponding Folder class. That
 * class should hold a set that points to the Messages in that Folder.
 */

#ifndef CHAPTER_13_EXERCISE_36_H_
#define CHAPTER_13_EXERCISE_36_H_

#include <cstddef>  // std::size_t
#include <set>      // std::set
#include <string>   // std::string

// Forward declaration for Folder
class Folder;

class Message {
  friend class Folder;
  friend void swap(Message& lhs, Message& rhs);

 public:
  // folders in implicitly initialized to the empty set
  explicit Message(const std::string& str = "") : contents(str) {}
  // copy control to manage pointers to this Message
  Message(const Message&);             // copy constructor
  Message& operator=(const Message&);  // copy assignment
  ~Message();                          // destructor

  std::size_t size() const;

  // add/remove this Message from the specified Folder's set of messages
  void save(Folder&);
  void remove(Folder&);
  // add/remove the folder to this Message
  void addFolder(Folder*);
  void remFolder(Folder*);

 private:
  void add_to_Folders(const Message&);
  void remove_from_Folders();

 private:
  std::string contents;       // actual message text
  std::set<Folder*> folders;  // Folders that have this Message
};

class Folder {
 public:
  Folder() = default;
  Folder(const Folder& folder);
  Folder& operator=(const Folder& folder);
  ~Folder();

  std::size_t size() const;

  void addMsg(Message* message);
  void remMsg(Message* message);

 private:
  void add_to_Messages(const Folder& rhs);
  void remove_from_Messages();

 private:
  std::set<Message*> messages_;
};

Message::Message(const Message& m) : contents(m.contents), folders(m.folders) {
  add_to_Folders(m);  // add this Message to the Folders that point to m
}

Message& Message::operator=(const Message& rhs) {
  // handle self-assignment by removing pointers before inserting them
  remove_from_Folders();    // update existing Folders
  contents = rhs.contents;  // copy message contents from rhs
  folders = rhs.folders;    // copy Folder pointers from rhs
  add_to_Folders(rhs);      // add this Message to those Folders
  return *this;
}

Message::~Message() { remove_from_Folders(); }

std::size_t Message::size() const { return folders.size(); }

void Message::save(Folder& f) {
  folders.insert(&f);  // add the given Folder to our list of Folders
  f.addMsg(this);      // add this Message to f's set of Messages
}

void Message::remove(Folder& f) {
  folders.erase(&f);  // take the given Folder out of our list of Folders
  f.remMsg(this);     // remove this Message to f's set of Messages
}

void Message::addFolder(Folder* folder) { folders.insert(folder); }

void Message::remFolder(Folder* folder) { folders.erase(folder); }

// add this Message to Folders that point to m
void Message::add_to_Folders(const Message& m) {
  for (auto f : m.folders)  // for each Folder that holds m
    f->addMsg(this);        // add a pointer to thies Message to that Folder
}

void Message::remove_from_Folders() {
  for (auto f : folders)  // for each pointer in folders
    f->remMsg(this);      // remove this Message from that Folder
  folders.clear();        // no Folder points to this Message
}

void swap(Message& lhs, Message& rhs) {
  using std::swap;  // not strictly needed in this case, but good habit
  // remove pointers each Message from their (original) respective Folders
  for (auto f : lhs.folders) f->remMsg(&lhs);
  for (auto f : rhs.folders) f->remMsg(&rhs);

  // swap the contents and Folder pointer sets
  swap(lhs.folders, rhs.folders);    // use swap(set&, set&)
  swap(lhs.contents, rhs.contents);  // swap(string&, string&)

  // add pointers to each Message to their (new) respective Folders
  for (auto f : lhs.folders) f->addMsg(&lhs);
  for (auto f : rhs.folders) f->addMsg(&rhs);
}

Folder::Folder(const Folder& folder) : messages_(folder.messages_) {
  add_to_Messages(folder);
}

Folder& Folder::operator=(const Folder& rhs) {
  remove_from_Messages();
  messages_ = rhs.messages_;
  add_to_Messages(rhs);
  return *this;
}

Folder::~Folder() { remove_from_Messages(); }

std::size_t Folder::size() const { return messages_.size(); }

void Folder::addMsg(Message* message) { messages_.insert(message); }

void Folder::remMsg(Message* message) { messages_.erase(message); }

void Folder::add_to_Messages(const Folder& folder) {
  for (auto* message : folder.messages_) message->addFolder(this);
}

void Folder::remove_from_Messages() {
  while (!messages_.empty()) (*messages_.begin())->remove(*this);
}

#endif  // CHAPTER_13_EXERCISE_36_H_
