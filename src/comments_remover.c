#include "comments_remover.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_stdint.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_vector.h"
#include <stdio.h>

JMS_XFER_PTR(jms_str) jms_cremover_run(JMS_BORROWED_PTR(jms_str) linesOfFile)
{
    JMS_XFER_PTR(jms_str) newLinesOfFile
        = jms_str_init("");

    printf("[%s]: newLinesOfFile == `%s`\n", __FUNCTION__, jms_str_cStr(newLinesOfFile));
    
    // Subtract 1 from the strlen to account for our 1 token of lookahead.
    for (ui32 i = 0; i < jms_str_len(linesOfFile) - 1; i++)
    {
        char curChar = jms_str_charAt(linesOfFile, i);
        bool doAppendChar = true;

        if (curChar == '/')
        {
            char nextChar = jms_str_charAt(linesOfFile, i + 1);

            if (nextChar == '/')
            {
                doAppendChar = false;

                // find newline or EOF
                ui32 commentEndIndex = i + 1;
                size_t fileLength = jms_str_len(linesOfFile);

                while (commentEndIndex < fileLength - 1)
                {
                    char curChar = jms_str_charAt(linesOfFile, commentEndIndex);
                    if (curChar == '\n')
                    {
                        printf("[%s]: found newline\n", __FUNCTION__);
                        break;
                    }
                    commentEndIndex++;
                }
                
                // Add a newline, still, so that the line numbers are correct.
                jms_str_append_cs(newLinesOfFile, "\n");

                // We've already lexed this code, skip ahead to the end of the comment.
                i = commentEndIndex;
            }
        }

        if (doAppendChar)
        {
            jms_str_append_ch(newLinesOfFile, curChar);
        }
    }

    char lastChar = jms_str_charAt(linesOfFile, jms_str_len(linesOfFile) - 1);
    jms_str_append_ch(newLinesOfFile, lastChar);

    return newLinesOfFile;
}