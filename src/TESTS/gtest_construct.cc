#include "../s21_viewer.h"

using namespace s21;

class ModelTest : public ::testing::Test {  // Правильное объявление фикстуры
 protected:
  void SetUp() override {
    model = new Model();
    normParams = NormalizationParameters(0.0, 0.0, 0.0, 0.0, 0.0);
    normParams2 = NormalizationParameters(1.0, -1.0, 0.05, 0.05, 0.05);
  }
  void TearDown() override { delete model; }
  Model *model;
  NormalizationParameters normParams;
  NormalizationParameters normParams2;
  ModelOperationResult result;
};

TEST_F(ModelTest, LoadValidModel) {
  result = model->LoadFigureToScene("TESTS/testobj1.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 1);
}

TEST_F(ModelTest, LoadValidModel2) {
  result = model->LoadFigureToScene("TESTS/test_pars.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 0);
}

TEST_F(ModelTest, LoadValidModel3) {
  result = model->LoadFigureToScene("obj_files/among.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 0);
}

TEST_F(ModelTest, LoadValidModel4) {
  result =
      model->LoadFigureToScene("obj_files/obj_models/among.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 1);
}
TEST_F(ModelTest, LoadValidModel5) {
  result = model->LoadFigureToScene("TESTS/invalid_vertex.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 0);
}
TEST_F(ModelTest, LoadValidModel6) {
  result = model->LoadFigureToScene("TESTS/invalid_faces.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 0);
}

TEST_F(ModelTest, LoadValidModel7) {
  result = model->LoadFigureToScene("TESTS/invalid_face2.obj", normParams);

  EXPECT_EQ(result.IsSuccess(), 0);
}

TEST_F(ModelTest, DiscretizationTest) {
  result =
      model->LoadFigureToScene("obj_files/obj_models/among.obj", normParams2);

  EXPECT_EQ(result.IsSuccess(), 1);
}