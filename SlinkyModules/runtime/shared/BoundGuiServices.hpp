#ifndef SLINKY_SHARE_4F47F3EE5CAB72EF7B3A
#define SLINKY_SHARE_4F47F3EE5CAB72EF7B3A
#include "CrtNativeBindings.hpp"
#include "DecodedNumericService.hpp"
#include "GuiRuntime.hpp"
#include "GuiPages.hpp"
#include "GuiModal.hpp"
#include "GuiDialogs.hpp"
#include "GuiConfigurationBindings.hpp"
#include "GuiProfileActions.hpp"
#include "DecodedDirectoryService.hpp"
namespace reconstruction::gui {
// 4C7B0 supplies the fixed DCDBE0 entry and six native payloads. The encoded
// target remains in caller-owned image/cell storage and is reloaded per call.
struct BoundProfileActionDependencies {
    const directory_service::Context &services;
    ProfileActionDependencies value;
    BoundProfileActionDependencies(const configuration::Dependencies &paths,
                                   const directory_service::Context &directory)
        :services(directory),value{paths,this,execute} {}
    BoundProfileActionDependencies(const BoundProfileActionDependencies &)=delete;
    static std::uint64_t execute(void *opaque,std::uint32_t,
        std::uint64_t owner,const std::uint16_t *operation,
        const std::uint16_t *path,std::uint64_t parameters,
        std::uint64_t directory,std::uint32_t show) {
        const auto &frame=*static_cast<BoundProfileActionDependencies *>(opaque);
        return directory_service::execute_dcdbe0(frame.services,owner,operation,
            path,parameters,directory,show);
    }
};
struct BoundControlDependencies {
    const ControlDependencies &source;
    const crt_service::Context *services;
    const DialogDependencies *dialogs;
    ControlDependencies value;
    BoundControlDependencies(const ControlDependencies &original,const drawing::FontDependencies &fonts,
                             const crt_service::Context *crt,const DialogDependencies *dialog=nullptr)
        :source(original),services(crt),dialogs(dialog),value{original.image,fonts,original.iconOrigins,
          original.closeCallback,this,copy,open} {}
    BoundControlDependencies(const BoundControlDependencies &)=delete;
    static void copy(void *opaque,char *destination,const char *text,std::uint64_t count) {
        auto &frame=*static_cast<BoundControlDependencies *>(opaque);
        if(frame.services)crt_service::copy_13d0b0(*frame.services,destination,text,count);
        else frame.source.copyTooltip_13d0b0(frame.source.context,destination,text,count);
    }
    static void open(void *opaque,std::uint8_t *state,std::uint64_t first,std::uint64_t second,const char *text) {
        const auto &frame=*static_cast<BoundControlDependencies *>(opaque);
        if(frame.dialogs){
            // The actual tabs caller supplies the literal "Unload Slinky?"
            // without conversion fields. It has no meaningful variadic word.
            openDialog_16820(state,first,second,text,nullptr,*frame.dialogs);
            return;
        }
        const auto &original=frame.source;
        original.openDialog_16820(original.context,state,first,second,text);
    }
};
// Preserve platform allocation/clock/context callbacks while connecting the
// ordinary dialog, load/save/delete and page bodies to caller-owned services.
struct BoundPageDependencies {
    const PageDependencies &source;
    const DialogDependencies *dialogs;
    const configuration::Dependencies *configuration;
    const ProfileActionDependencies *actions;
    PageDependencies value;
    BoundPageDependencies(const PageDependencies &original,const ControlDependencies &controls,
        const DialogDependencies *dialog,const configuration::Dependencies *paths,
        const ProfileActionDependencies *profileActions,RecoveredFrameInvoker calls)
        :source(original),dialogs(dialog),configuration(paths),actions(profileActions),
         value{controls,original.input,original.image,this,allocate,allocateZeroed,clock,open,
           load,directory,remove,save,original.completionCallback_139d0,calls,
           original.listMemory,original.hexFilterCallback_18830} {}
    BoundPageDependencies(const BoundPageDependencies &)=delete;
    static void *allocate(void *p,std::uint64_t bytes){const auto &s=static_cast<BoundPageDependencies *>(p)->source;return s.allocate(s.context,bytes);}
    static void *allocateZeroed(void *p,std::uint64_t count,std::uint64_t stride){const auto &s=static_cast<BoundPageDependencies *>(p)->source;return s.allocateZeroed(s.context,count,stride);}
    static double clock(void *p){const auto &s=static_cast<BoundPageDependencies *>(p)->source;return s.clock(s.context);}
    static void open(void *p,std::uint8_t *state,std::uint64_t user,std::uint64_t completion,const char *title,const char *initial){
        const auto &f=*static_cast<BoundPageDependencies *>(p);
        if(f.dialogs)openDialogText_16820(state,user,completion,title,initial,*f.dialogs);
        else f.source.openDialog_16820(f.source.context,state,user,completion,title,initial);
    }
    static std::uint32_t load(void *p,const char *name,std::uint64_t manager){
        const auto &f=*static_cast<BoundPageDependencies *>(p);
        if(f.configuration)return configuration::loadProfile_be40(reinterpret_cast<const std::uint8_t *>(name),reinterpret_cast<const std::uint8_t *>(std::uintptr_t(manager)),*f.configuration);
        return f.source.loadProfile_be40(f.source.context,name,manager);
    }
    static std::uint32_t directory(void *p){
        const auto &f=*static_cast<BoundPageDependencies *>(p);
        if(f.actions)return openProfileDirectory_c290(*f.actions);
        return f.source.openProfileDirectory_c290(f.source.context);
    }
    static std::uint32_t remove(void *p,const char *name){
        const auto &f=*static_cast<BoundPageDependencies *>(p);
        if(f.configuration)return deleteProfile_c220(name,*f.configuration);
        return f.source.deleteProfile_c220(f.source.context,name);
    }
    static std::uint32_t save(void *p,const char *name,std::uint8_t replace,std::uint64_t manager){
        const auto &f=*static_cast<BoundPageDependencies *>(p);
        if(f.configuration)return configuration::saveProfile_c0b0(reinterpret_cast<const std::uint8_t *>(name),replace,reinterpret_cast<const std::uint8_t *>(std::uintptr_t(manager)),*f.configuration);
        return f.source.saveProfile_c0b0(f.source.context,name,replace,manager);
    }
};
inline PageCalls pageCalls(const PageDependencies &pages){
    return {const_cast<PageDependencies *>(&pages),
      [](void *p,std::uint8_t *s,std::uint8_t *u,std::uint64_t manager,std::uint32_t category,float elapsed){renderCategory_12b20(s,u,manager,category,elapsed,*static_cast<const PageDependencies *>(p));},
      [](void *p,std::uint8_t *s,std::uint8_t *u,std::uint64_t metadata,std::uint8_t *record,std::uint32_t key,std::uint64_t flag,float *rect){profileTextInput_13420(s,u,metadata,record,key,reinterpret_cast<std::uint8_t *>(std::uintptr_t(flag)),rect,*static_cast<const PageDependencies *>(p));},
      [](void *p,std::uint8_t *s,std::uint64_t manager,std::uint64_t configuration,const char *name,std::uint32_t mode){profilePopup_138f0(s,manager,configuration,name,mode,*static_cast<const PageDependencies *>(p));},
      [](void *p,std::uint8_t *s,std::uint8_t *u){renderModal_16ca0(s,u,*static_cast<const PageDependencies *>(p));}};
}
struct BoundRuntimeDependencies {
    const RuntimeDependencies &source;
    const numeric_service::Context *scalar;
    const crt_service::Context *strings;
    RuntimeDependencies value;
    BoundRuntimeDependencies(const RuntimeDependencies &original,const ControlDependencies &controls,
                             const numeric_service::Context *numeric,const crt_service::Context *crt,
                             const PageCalls *pages=nullptr,const ConfigurationCalls *configuration=nullptr)
        :source(original),scalar(numeric),strings(crt),value{controls,configuration?*configuration:original.configuration,pages?*pages:original.pages,
          this,power,compare,original.profileNameCallback_13ad0} {}
    BoundRuntimeDependencies(const BoundRuntimeDependencies &)=delete;
    static float power(void *opaque,float first,float second) {
        auto &frame=*static_cast<BoundRuntimeDependencies *>(opaque);
        if(frame.scalar)return numeric_service::binaryScalar_13cfe0(*frame.scalar,first,second);
        return frame.source.binaryScalar_13cfe0(frame.source.protectedContext,first,second);
    }
    static std::int32_t compare(void *opaque,std::uint64_t first,std::uint64_t second) {
        auto &frame=*static_cast<BoundRuntimeDependencies *>(opaque);
        if(frame.strings)return crt_service::compare_13d0a0(*frame.strings,
            reinterpret_cast<const char *>(std::uintptr_t(first)),reinterpret_cast<const char *>(std::uintptr_t(second)));
        return frame.source.compare_13d0a0(frame.source.protectedContext,first,second);
    }
};
}
#endif // SLINKY_SHARE_4F47F3EE5CAB72EF7B3A
