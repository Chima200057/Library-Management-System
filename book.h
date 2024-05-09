#ifndef BOOK_H
#define BOOK_H

class Book {
public:
  // Constructor and destructor
  Book(int id, std::string name, std::string author, std::string type, int pageCount);
  Book();

  // Getters and setters
  int getBookID() const;
  std::string getBookName() const;
  std::string getAuthor() const;
  std::string getType() const;
  int getPageCount() const;
  int getBorrowerID() const;
  std::string getDueDate() const;

  void setBorrowerID(int borrowerID);
  void setDueDate(const std::string& dueDate);

  // Other methods
  bool isAvailable() const;
  std::string toString() const;

private:
  // Member variables
  int id_;
  std::string name_;
  std::string author_;
  std::string type_;
  int pageCount_;
  int borrowerID_;
  std::string dueDate_;
};

#endif
