#include "comments_remover.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_stdint.h"
#include "jms_utils/jms_str.h"

JMS_XFER_PTR(jms_str) jms_cremover_run(JMS_BORROWED_PTR(jms_str) linesOfFile)
{
    JMS_XFER_PTR(jms_str) newLinesOfFile
        = jms_str_init_str(linesOfFile);

    // Subtract 1 from the strlen to account for our 1 token of lookahead.
    for (ui32 i = 0; i < jms_str_len(linesOfFile) - 1; i++)
    {
        char curChar = jms_str_charAt(linesOfFile, i);

        if (curChar == '/')
        {
            char nextChar = jms_str_charAt(linesOfFile, i + 1);

            if (nextChar == '/')
            {
                // find newline or EOF
                ui32 commentEndIndex = i + 1;
                size_t fileLength = jms_str_len(linesOfFile);

                while (commentEndIndex < fileLength)
                {
                    char curChar = jms_str_charAt(linesOfFile, commentEndIndex);
                    if (curChar == '\n')
                    {
                        break;
                    }
                    commentEndIndex++;

                    if (commentEndIndex > fileLength)
                    {
                        commentEndIndex = fileLength;
                    }
                }

                JMS_XFER_PTR(jms_str) newLines = jms_str_substr(linesOfFile, i, commentEndIndex - 1);
                jms_str_del(newLinesOfFile);
                newLinesOfFile = newLines;
            }
        }
    }

    return newLinesOfFile;
}