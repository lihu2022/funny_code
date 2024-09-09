#include <iostream>
#include <memory>



class grandpa{
public:
  virtual ~grandpa() {};
  virtual void sendtrigger(const int param1, double num) const = 0;
};

class father1 : public grandpa{
public:
  father1() : grandpa() {}
  virtual ~father1() {}
  void sendtrigger(const int param1, double num) const override {
    this->Check(param1, num);
  }
protected:
  void Check(const int param1, double num) const {
    std::cout<<"now excuting father1 class :::Check()"<<std::endl;
  };
  bool update(const int param1);
};


class father2 : public grandpa {
public:
  father2(std::shared_ptr<grandpa>base_check) : grandpa(), base_checker(base_check) {}
  ~father2() {}

  void sendtrigger(const int param1, double num) const override {
    return this->base_checker->sendtrigger(param1, num);
  }

private:
  std::shared_ptr<grandpa>base_checker;
};

class son1 : public father2 {
public:
  son1(std::shared_ptr<grandpa>base_check) : father2(base_check) {}
  ~son1() {}

  void sendtrigger(const int param1, double num) const override {
    father2::sendtrigger(param1, num);
    this->Check(param1, num);
  }


protected:
  void Check(const int param2, double num2) const {
    std::cout<<"now excuting son1 class ::::Check()"<<std::endl;
  };
  bool update();


};

class son2 : public father2 {
public:
  son2(std::shared_ptr<grandpa>base_check) : father2(base_check) {}
  ~son2() {}

  void sendtrigger(const int param1, double num) const override {
    father2::sendtrigger(param1, num);
    this->Check(param1, num);
  }


protected:
  void Check(const int numa, double numb) const {
    std::cout<<"now excuting son2 class ::::Check()"<<std::endl;
  };
  void update();

};



int main() {

  std::shared_ptr<grandpa> base_1 = std::make_shared<father1>();
  std::shared_ptr<grandpa> base_2 = std::make_shared<father2>(base_1);
  std::shared_ptr<grandpa> base_3 = std::make_shared<son1>(base_2);
  std::shared_ptr<grandpa> base_4 = std::make_shared<son2>(base_3);

  const int a = 5;
  double b = 7;
  base_4->sendtrigger(a, b);



  std::cout << "hello world" << std::endl;
  return 0;
}

