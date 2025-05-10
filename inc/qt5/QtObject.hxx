/* comment */
#pragma once

#include <salobj.hxx>
#include <vcl/sysdata.hxx>

#include <QtCore/QObject>
#include <QtGui/QRegion>
#include <QtWidgets/QWidget>

class QtFrame;
class QtObjectWidget;
class QWindow;

class QtObject final : public QObject, public SalObject
{
    Q_OBJECT

    SystemEnvData m_aSystemData;
    QtFrame* m_pParent;
    QtObjectWidget* m_pQWidget;
    QRegion m_pRegion;
    bool m_bForwardKey;

public:
    QtObject(QtFrame* pParent, bool bShow);
    ~QtObject() override;

    QtFrame* frame() const { return m_pParent; }
    inline QWidget* widget() const;
    QWindow* windowHandle() const;
    bool forwardKey() const { return m_bForwardKey; }

    virtual void ResetClipRegion() override;
    virtual void BeginSetClipRegion(sal_uInt32 nRects) override;
    virtual void UnionClipRegion(tools::Long nX, tools::Long nY, tools::Long nWidth,
                                 tools::Long nHeight) override;
    virtual void EndSetClipRegion() override;

    virtual void SetPosSize(tools::Long nX, tools::Long nY, tools::Long nWidth,
                            tools::Long nHeight) override;
    virtual void Show(bool bVisible) override;

    virtual void SetForwardKey(bool bEnable) override;

    virtual const SystemEnvData* GetSystemData() const override { return &m_aSystemData; }

    virtual void Reparent(SalFrame* pFrame) override;
};

class QtObjectWidget final : public QWidget
{
    QtObject& m_rParent;

    void focusInEvent(QFocusEvent*) override;
    void focusOutEvent(QFocusEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

public:
    explicit QtObjectWidget(QtObject& rParent);
};

QWidget* QtObject::widget() const { return m_pQWidget; }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
