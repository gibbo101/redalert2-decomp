#include "shared/scenario_checkpoint.hpp"
#include "shared/com_persist.hpp"
void ScenarioCheckpoint_004B5A70::Read_004B5C50(IStream *stream)
{
    stream->Read(this,sizeof(*this),0);
}
