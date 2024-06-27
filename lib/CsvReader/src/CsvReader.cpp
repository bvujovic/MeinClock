#include "CsvReader.h"

CsvReader::CsvReader(const char *path, byte cntParts)
{
    this->cntParts = cntParts;
    fp = LittleFS.open(path, "r");
}

String *CsvReader::readLine()
{
    if (!fileOpenSuccess())
        return NULL;
    if (!fp.available())
    {
        fp.close();
        return NULL;
    }
    String l = fp.readStringUntil('\n');
    String *ss = new String[cntParts];
    int idx = 0;

    for (size_t i = 0; i < cntParts; i++)
    {
        idx = l.indexOf(sepParts, idx);
        if (idx == -1)
            break;
        ss[i] = l.substring(0, idx);
        idx += ss[i].length();
    }
    ss[cntParts - 1] = l.substring(l.lastIndexOf(sepParts)+1);
    return ss;
}
