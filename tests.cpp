#include "nortan_exam.cpp"
#include <gtest/gtest.h>

TEST(FileLocationTest, FileNodes) {
  ASSERT_EQ(true, check_valid_file_name("/dev/nortan"))
      << "\t Must have Failed for /dev/nortan\n";
  ASSERT_EQ(true, check_valid_file_name("/dev/null"))
      << "\t Must have Failed for /dev/null\n";
}

TEST(FileLocationTest, DirectoryNodes) {
  ASSERT_EQ(true, check_valid_file_name("/tmp"))
      << "\t Must have Failed for /tmp\n";
  ASSERT_EQ(true, check_valid_file_name("/home"))
      << "\t Must have Failed for /home\n";
}

TEST(FileWriteTest, FileNames) {

  char *fName = "/dev/tmp";

  int fd = open(fName, O_RDONLY | O_APPEND | O_CREAT, 0644);

  ASSERT_EQ(false, make_file_for_writing(fName))
      << "\n Must Have failed because I provided read mode file\n";

  close(fd);
}

TEST(CheckFileReadWrite, BufferValidation) {
  char *fname = "/tmp/testNortanIn.txt";

  int fdW = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);

  std::string InBuffer("Hello Nortan Tets, Let's test md5sum");
  std::string Obuffer;

  write(fdW, InBuffer.data(), InBuffer.size());

  read_write_loop(fname, "/tmp/testNortanOp.txt", true);

  int fdR = open("/tmp/testNortanOp.txt", O_RDONLY | O_APPEND | O_CREAT, 0644);

  char bb[InBuffer.size()];
  read(fdR, bb, InBuffer.size());

  //   ASSERT_STREQ(InBuffer, "hello world") << "\n This must fail";
  //   ASSERT_STREQ(InBuffer, "Hello Nortan Tets, Let's test md5sum") << "\n
  //   This must not fail";
  Obuffer = bb;

  ASSERT_EQ(InBuffer, Obuffer);

  close(fdR);
  close(fdW);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
