/**
 *  @file   ContentData.cpp
 *  @author Blurred-9L
 */

#include "ContentData.h"

/**
 *  @details    Constructs a ContentData object with invalid values.
 */
ContentData::ContentData() : startLine_(-1), startIndex_(-1), endLine_(-1), endIndex_(-1)
{
}

/**
 *  @details    Constructs a ContentData object with the given values.
 *
 *  @param[in]  startLine           The line at which the contents start.
 *  @param[in]  startIndex          The character index at which the contents start.
 *  @param[in]  endLine             The line at which the contents end.
 *  @param[in]  endIndex            The character index of the first character not part of the contents.
 */
ContentData::ContentData(int startLine, int startIndex, int endLine, int endIndex) :
    startLine_(startLine), startIndex_(startIndex), endLine_(endLine), endIndex_(endIndex)
{
}

/**
 *  @details    Get-method for the start line member.
 *
 *  @return     The value of the start line member.
 */
int ContentData::startLine() const
{
    return startLine_;
}

/**
 *  @details    Get-method for the start index member.
 *
 *  @return     The value of the start index member.
 */
int ContentData::startIndex() const
{
    return startIndex_;
}

/**
 *  @details    Get-method for the end line member.
 *
 *  @return     The value of the end line member.
 */
int ContentData::endLine() const
{
    return endLine_;
}

/**
 *  @details    Get-method for the end index member.
 *
 *  @return     The value of the end index member.
 */
int ContentData::endIndex() const
{
    return endIndex_;
}
