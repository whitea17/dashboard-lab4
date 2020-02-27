#ifndef SENSITIVEINFOHANDLER_H
#define SENSITIVEINFOHANDLER_H
//
// Note: I know this isn't by any means secure. The only thing this class is for is
//       keeping sensitive information from reaching a public git repo. A base
//       of this class will be commitied but after that no future commits should
//       happen.
//

class SensitiveInfoHandler
{
public:
    SensitiveInfoHandler();
    // All passwords and api keys will go here
};

#endif // SENSITIVEINFOHANDLER_H
