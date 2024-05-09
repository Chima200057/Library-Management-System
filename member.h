#ifndef MEMBER_H
#define MEMBER_H

class Member {
public:
  // Constructor and destructor
  Member(int id, std::string name, std::string address, std::string email);
  Member();

  // Getters and setters
  int getMemberID() const;
  std::string getName() const;
  std::string getAddress() const;
  std::string getEmail() const;

  // Other methods
  std::string toString() const;

private:
  // Member variables
  int id_;
  std::string name_;
  std::string address_;
  std::string email_;
};

#endif
