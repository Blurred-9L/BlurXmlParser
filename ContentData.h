/**
 *  @file   ContentData.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_CONTENT_DATA_H
#define XML_PARSER_CONTENT_DATA_H

/**
 *  @class  ContentData
 *
 *  @brief  Storage class used to determine the location at which
 *          the contents of a xml tag start and end.
 */
class ContentData {
private:
    /// The start line
    int startLine_;
    /// The start index
    int startIndex_;
    /// The end line
    int endLine_;
    /// The end index
    int endIndex_;
    
public:
    /// Default constructor
    ContentData();
    /// Constructor
    ContentData(int startLine, int startIndex, int endLine, int endIndex);
    /// Gets start line
    int startLine() const;
    /// Gets start index
    int startIndex() const;
    /// Gets end line
    int endLine() const;
    /// Gets end index
    int endIndex() const;
};

#endif /// NOT XML_PARSER_CONTENT_DATA_H
