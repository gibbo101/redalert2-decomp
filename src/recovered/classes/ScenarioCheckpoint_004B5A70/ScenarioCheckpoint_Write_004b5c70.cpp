#include "shared/scenario_checkpoint.hpp"
#include "shared/com_persist.hpp"
void ScenarioCheckpoint_004B5A70::Write_004B5C70(IStream *stream)
{
    stream->Write(this,sizeof(*this),0);
}
