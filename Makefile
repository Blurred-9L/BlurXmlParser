# -*- indent-tabs-mode:t -*-

OBJECTS = AttrNode.o \
		  ContentData.o \
		  StringHasher.o \
		  TagNode.o \
		  XmlArray.o \
		  XmlAutomata.o \
		  XmlContentManager.o \
		  XmlDictionary.o \
		  XmlDocument.o \
		  XmlNestingError.o \
		  XmlNoKeyFound.o \
		  XmlObject.o \
		  XmlObjectBuilder.o \
		  XmlOutOfTokens.o \
		  XmlParser.o \
		  XmlSyntaxError.o \
		  XmlValue.o \
		  XmlWrapper.o
		  
SOURCES = $(OBJECTS:.o=.cpp)
HEADERS = $(OBJECTS:.o=.h)

BLUR_PARSER_OBJS = BlurParser/ErrorData.o \
				   BlurParser/ErrorKeeper.o \
				   BlurParser/LineFileReader.o \
				   BlurParser/Token.o \
				   BlurParser/TokenData.o \
				   BlurParser/AbstractAutomata.o \
				   BlurParser/KeywordSet.o \
				   BlurParser/Tokenizer.o \
				   BlurParser/Parser.o \
				   BlurParser/ParserTable.o \
				   BlurParser/ParserTableAction.o \
				   BlurParser/ParserTableKey.o
				   
CFLAGS = -Wall -Wextra

all: blurparser $(OBJECTS)

blurparser:
	cd BlurParser && make

AttrNode.o: AttrNode.cpp AttrNode.h
	g++ -c $(CFLAGS) AttrNode.cpp
	
ContentData.o: ContentData.cpp ContentData.h
	g++ -c $(CFLAGS) ContentData.cpp
	
StringHasher.o: StringHasher.cpp StringHasher.h
	g++ -c $(CFLAGS) StringHasher.cpp
	
TagNode.o: TagNode.cpp TagNode.h
	g++ -c $(CFLAGS) TagNode.cpp
	
XmlArray.o: XmlArray.cpp XmlArray.h
	g++ -c $(CFLAGS) XmlArray.cpp
	
XmlAutomata.o: XmlAutomata.cpp XmlAutomata.h
	g++ -c $(CFLAGS) XmlAutomata.cpp
	
XmlContentManager.o: XmlContentManager.cpp XmlContentManager.h
	g++ -c $(CFLAGS) XmlContentManager.cpp
	
XmlDictionary.o: XmlDictionary.cpp XmlDictionary.h
	g++ -c $(CFLAGS) XmlDictionary.cpp
	
XmlDocument.o: XmlDocument.cpp XmlDocument.h
	g++ -c $(CFLAGS) XmlDocument.cpp
	
XmlNestingError.o: XmlNestingError.cpp XmlNestingError.h
	g++ -c $(CFLAGS) XmlNestingError.cpp
	
XmlNoKeyFound.o: XmlNoKeyFound.cpp XmlNoKeyFound.h
	g++ -c $(CFLAGS) XmlNoKeyFound.cpp
	
XmlObject.o: XmlObject.cpp XmlObject.h
	g++ -c $(CFLAGS) XmlObject.cpp
	
XmlObjectBuilder.o: XmlObjectBuilder.cpp XmlObjectBuilder.h
	g++ -c $(CFLAGS) XmlObjectBuilder.cpp
	
XmlOutOfTokens.o: XmlOutOfTokens.cpp XmlOutOfTokens.h
	g++ -c $(CFLAGS) XmlOutOfTokens.cpp
	
XmlParser.o: XmlParser.cpp XmlParser.h
	g++ -c $(CFLAGS) XmlParser.cpp
	
XmlSyntaxError.o: XmlSyntaxError.cpp XmlSyntaxError.h
	g++ -c $(CFLAGS) XmlSyntaxError.cpp
	
XmlValue.o: XmlValue.cpp XmlValue.h
	g++ -c $(CFLAGS) XmlValue.cpp
	
XmlWrapper.o: XmlWrapper.cpp XmlWrapper.h
	g++ -c $(CFLAGS) XmlWrapper.cpp
	
clean:
	rm -rf $(OBJECTS)
	cd BlurParser && make clean
