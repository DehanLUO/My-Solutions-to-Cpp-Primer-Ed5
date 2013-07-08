/*
 * Exercise 13.37: Add members to the Message class to insert or remove a given
 * Folder* into folders. These members are analogous to Folder’s addMsg and
 * remMsg operations.
 */

#ifndef CHAPTER_13_EXERCISE_37_H_
#define CHAPTER_13_EXERCISE_37_H_

#include <cstddef>  // std::size_t
#include <set>      // std::set
#include <string>   // std::string

// Forward declaration for Folder
class Folder;

/**
 * @class Message
 * @brief Represents a text message that can be stored in multiple folders
 *
 * Maintains a set of Folder pointers that contain this message, with
 * corresponding methods to manage the bidirectional relationship.
 */
class Message {
  friend class Folder;

  /**
   * @brief Specialized swap operation for Folder objects
   * @param lhs First Folder to swap
   * @param rhs Second Folder to swap
   * @note Maintains all bidirectional relationships during the swap
   * time O(n + m) where n,m are message counts
   */
  friend void swap(Message &lhs, Message &rhs);

 public:
  /**
   * @brief Construct a new Message with given content
   * @param str The message content (default empty string)
   */
  explicit Message(const std::string &str = "");

  /**
   * @brief Copy constructor
   * @param other The Message to copy from
   * @note Performs deep copy of contents and folder relationships
   */
  Message(const Message &other);

  /**
   * @brief Copy assignment operator
   * @param rhs The Message to assign from
   * @return Reference to this Message
   * @note Provides strong exception guarantee
   */
  Message &operator=(const Message &rhs);

  /**
   * @brief Destructor
   * @note Automatically removes this Message from all containing Folders
   */
  ~Message();

  /**
   * @brief Add this Message to a Folder's collection
   * @param folder Reference to the target Folder
   */
  void Save(Folder &folder);

  /**
   * @brief Remove this Message from a Folder's collection
   * @param folder Reference to the target Folder
   */
  void Remove(Folder &folder);

  /**
   * @brief Add a Folder pointer to this Message's folder set
   * @param folder Pointer to the Folder to add
   * @note Only updates the Message's side of the relationship
   */
  void AddFolder(Folder *folder);

  /**
   * @brief Remove a Folder pointer from this Message's folder set
   * @param folder Pointer to the Folder to remove
   * @note Only updates the Message's side of the relationship
   */
  void RemoveFolder(Folder *folder);

  /**
   * @brief Get the number of Folders containing this Message
   * @return std::size_t Count of containing Folders
   */
  std::size_t size() const;

 private:
  /**
   * @brief Helper to add this Message to all Folders in its set
   */
  void AddThisToFolders();

  /**
   * @brief Helper to remove this Message from all Folders in its set
   */
  void RemoveThisFromFolders();

 private:
  std::string contents_;        // actual message text
  std::set<Folder *> folders_;  // Folders that have this meesage
};

/**
 * @class Folder
 * @brief Represents a collection of Message objects
 *
 * Maintains a set of Message pointers contained in this folder, with
 * corresponding methods to manage the bidirectional relationship.
 */
class Folder {
  friend class Message;
  friend void swap(Folder &, Folder &);

 public:
  /**
   * @brief Default constructor - creates an empty Folder
   * @note Constructed Folder contains no Messages
   */
  Folder() = default;

  /**
   * @brief Copy constructor - creates a new Folder with identical Message
   * associations
   * @param other The Folder to copy from
   * @note The new Folder will be added to all Messages in the original Folder
   * time O(n) where n is number of Messages
   */
  Folder(const Folder &other);

  /**
   * @brief Copy assignment operator
   * @param rhs The Folder to assign from
   * @return Reference to this Folder
   * @note Provides strong exception guarantee. Handles self-assignment.
   * time O(n) where n is total Messages in both Folders
   */
  Folder &operator=(const Folder &rhs);

  /**
   * @brief Destructor - removes this Folder from all contained Messages
   * time O(n) where n is number of Messages
   */
  ~Folder();

  /**
   * @brief Adds a Message to this Folder's collection
   * @param msg Pointer to the Message to add
   * @note Also adds this Folder to the Message's folder set
   * time O(log n) for set insertion
   */
  void AddMessage(Message *msg);

  /**
   * @brief Removes a Message from this Folder's collection
   * @param msg Pointer to the Message to remove
   * @note Also removes this Folder from the Message's folder set
   * time O(log n) for set erasure
   */
  void RemoveMessage(Message *msg);

  /**
   * @brief Returns the number of Messages in this Folder
   * @return std::size_t Count of contained Messages
   * time O(1)
   */
  std::size_t size() const;

 private:
  /**
   * @brief Helper function to add this Folder to all contained Messages
   * @note Used during copy operations to establish bidirectional links
   * time O(n) where n is number of Messages
   */
  void AddThisToMessages();

  /**
   * @brief Helper function to remove this Folder from all contained Messages
   * @note Used during destruction and assignment to clean up relationships
   * time O(n) where n is number of Messages
   */
  void RemoveThisFromMessages();

 private:
  std::set<Message *> messages_;  // Messages contained in this folder
};

// Message member function implementations

inline Message::Message(const std::string &str) : contents_(str) {}

inline Message::Message(const Message &other)
    : contents_(other.contents_), folders_(other.folders_) {
  AddThisToFolders();  // add this Message to the Folders that point to m
}

inline Message &Message::operator=(const Message &rhs) {
  // handle self-assignment by removing pointers before inserting them
  if (this != &rhs) {
    RemoveThisFromFolders();    // remove current Message from its Folders
    contents_ = rhs.contents_;  // copy message contents from rhs
    folders_ = rhs.folders_;    // copy Folder pointers from rhs
    AddThisToFolders();         // add this Message to those Folders
  }
  return *this;
}

inline Message::~Message() { RemoveThisFromFolders(); }

inline void Message::Save(Folder &folder) {
  folders_.insert(&folder);
  folder.AddMessage(this);  // add this Message to f's set of Messages
}

inline void Message::Remove(Folder &folder) {
  folders_.erase(&folder);
  folder.RemoveMessage(this);  // remove this Message to f's set of Messages
}

inline void Message::AddFolder(Folder *folder) { folders_.insert(folder); }
inline void Message::RemoveFolder(Folder *folder) { folders_.erase(folder); }

std::size_t Message::size() const { return folders_.size(); }

inline void Message::AddThisToFolders() {
  for (auto *folder : folders_)  // for each Folder that holds m
    folder->AddMessage(this);    // add a pointer to this Message to that Folder
}

inline void Message::RemoveThisFromFolders() {
  for (auto *folder : folders_) {
    folder->RemoveMessage(this);
  }
}

inline void swap(Message &lhs, Message &rhs) {
  lhs.RemoveThisFromFolders();
  rhs.RemoveThisFromFolders();

  // swap the contents and Folder pointer sets
  std::swap(lhs.folders_, rhs.folders_);    // uses swap(set&, set&)
  std::swap(lhs.contents_, rhs.contents_);  // swap(string&, string&)

  lhs.AddThisToFolders();
  rhs.AddThisToFolders();
}

// Folder member function implementations

inline Folder::Folder(const Folder &other) : messages_(other.messages_) {
  AddThisToMessages();  // Add this folder to all messages
}

inline Folder::~Folder() {
  RemoveThisFromMessages();  // Remove this folder from all messages
}

inline Folder &Folder::operator=(const Folder &rhs) {
  if (this != &rhs) {
    RemoveThisFromMessages();   // Remove from current messages
    messages_ = rhs.messages_;  // Copy message pointers
    AddThisToMessages();        // Add to new messages
  }
  return *this;
}

inline void Folder::AddMessage(Message *msg) {
  messages_.insert(msg);  // Add message to folder's set
}

inline void Folder::RemoveMessage(Message *msg) {
  messages_.erase(msg);  // Remove message from folder's set
}

inline std::size_t Folder::size() const { return messages_.size(); }

inline void Folder::AddThisToMessages() {
  for (auto *msg : messages_) {
    msg->AddFolder(this);  // Add this folder to each message
  }
}

inline void Folder::RemoveThisFromMessages() {
  for (auto *msg : messages_) {
    msg->RemoveFolder(this);  // Remove this folder from each message
  }
}

inline void swap(Folder &lhs, Folder &rhs) {
  // Remove folders from their current messages
  lhs.RemoveThisFromMessages();
  rhs.RemoveThisFromMessages();

  // Swap message sets
  std::swap(lhs.messages_, rhs.messages_);

  // Add folders to their new messages
  lhs.AddThisToMessages();
  rhs.AddThisToMessages();
}

#endif  // CHAPTER_13_EXERCISE_37_H_