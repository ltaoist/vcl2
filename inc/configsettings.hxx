/* comment */#ifndef INCLUDED_VCL_CONFIGSETTINGS_HXX
#define INCLUDED_VCL_CONFIGSETTINGS_HXX

#include <rtl/ustring.hxx>
#include <unotools/configitem.hxx>
#include <vcl/dllapi.h>

#include <unordered_map>

namespace com::sun::star::uno { template <typename > class Sequence; }

namespace vcl
{
    typedef std::unordered_map< OUString, OUString > OUStrMap;
    class SmallOUStrMap : public OUStrMap { public: SmallOUStrMap() : OUStrMap(1) {} };


    //= SettingsConfigItem

    class VCL_DLLPUBLIC SettingsConfigItem final : public ::utl::ConfigItem
    {
    private:
        std::unordered_map< OUString, SmallOUStrMap > m_aSettings;

        virtual void Notify( const css::uno::Sequence< OUString >& rPropertyNames ) override;

        void getValues();
        SettingsConfigItem();

        virtual void ImplCommit() override;

    public:
        virtual ~SettingsConfigItem() override;

        static SettingsConfigItem* get();

        OUString getValue( const OUString& rGroup, const OUString& rKey ) const;
        void setValue( const OUString& rGroup, const OUString& rKey, const OUString& rValue );

    };


} // namespace vcl


#endif // INCLUDED_VCL_CONFIGSETTINGS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
