CXXFLAGS=-fPIC -std=c++2a -Iapi -w -g
TARGET=WShabtiPict
TARGET_LIB_SO=libpict.so
OBJS = $(OBJS_SOURCE)
OBJS_SOURCE =  wshabtilib/api/combination.o wshabtilib/api/deriver.o wshabtilib/api/exclusion.o
OBJS_SOURCE += wshabtilib/api/model.o wshabtilib/api/parameter.o wshabtilib/api/pictapi.o
OBJS_SOURCE += wshabtilib/api/task.o wshabtilib/api/worklist.o
OBJS_SOURCE += wshabtilib/utils/utils.o
OBJS_SOURCE += wshabtilib/input-parser/input-parser.o
OBJS_SOURCE += wshabtilib/java-source-code-parser/java-source-code-parser.o
OBJS_SOURCE += wshabtilib/junit-test-case-generator/junit-test-case-generator.o
OBJS_SOURCE += wshabtilib/oracle-generator/oracle-generator.o
OBJS_SOURCE += wshabtilib/case-test-generator/case-test-generator.o
OBJS_SOURCE += main/WShabtiPict.o

wshabti_pict: $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(TARGET_LIB_SO): $(OBJS_SOURCE)
	$(CXX) -fPIC -shared $(OBJS_SOURCE) -o $(TARGET_LIB_SO)

clean:
	rm -f $(TARGET) $(TARGET_LIB_SO) $(OBJS)

all: wshabti_pict $(TARGET_LIB_SO)