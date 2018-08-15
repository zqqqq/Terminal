#pragma once

#include "..\..\renderer\inc\RenderEngineBase.hpp"

namespace Microsoft::Console::Render
{
    class WddmConEngine final : public RenderEngineBase
    {
    public:
        WddmConEngine();
        ~WddmConEngine() override;

        [[nodiscard]]
        HRESULT Initialize() noexcept;
        bool IsInitialized();

        // Used to release device resources so that another instance of
        // conhost can render to the screen (i.e. only one DirectX
        // application may control the screen at a time.)
        [[nodiscard]]
        HRESULT Enable() noexcept;
        [[nodiscard]]
        HRESULT Disable() noexcept;

        RECT GetDisplaySize();

        // IRenderEngine Members
        [[nodiscard]]
        HRESULT Invalidate(const SMALL_RECT* const psrRegion) noexcept override;
        [[nodiscard]]
        HRESULT InvalidateCursor(const COORD* const pcoordCursor) noexcept override;
        [[nodiscard]]
        HRESULT InvalidateSystem(const RECT* const prcDirtyClient) noexcept override;
        [[nodiscard]]
        HRESULT InvalidateSelection(const SMALL_RECT rect) noexcept override;
        [[nodiscard]]
        HRESULT InvalidateScroll(const COORD* const pcoordDelta) noexcept override;
        [[nodiscard]]
        HRESULT InvalidateAll() noexcept override;
        [[nodiscard]]
        HRESULT InvalidateCircling(_Out_ bool* const pForcePaint) noexcept override;
        [[nodiscard]]
        HRESULT PrepareForTeardown(_Out_ bool* const pForcePaint) noexcept override;

        [[nodiscard]]
        HRESULT StartPaint() noexcept override;
        [[nodiscard]]
        HRESULT EndPaint() noexcept override;
        [[nodiscard]]
        HRESULT Present() noexcept override;
        
        
        [[nodiscard]]
        HRESULT ScrollFrame() noexcept override;

        [[nodiscard]]
        HRESULT PaintBackground() noexcept override;
        [[nodiscard]]
        HRESULT PaintBufferLine(PCWCHAR const pwsLine,
                                const unsigned char* const rgWidths,
                                size_t const cchLine,
                                COORD const coord,
                                bool const fTrimLeft,
                                const bool lineWrapped) noexcept override;
        [[nodiscard]]
        HRESULT PaintBufferGridLines(GridLines const lines, COLORREF const color, size_t const cchLine, COORD const coordTarget) noexcept override;
        [[nodiscard]]
        HRESULT PaintSelection(const std::vector<SMALL_RECT>& rectangles) noexcept override;

        [[nodiscard]]
        HRESULT PaintCursor(const COORD coordCursor,
                            const ULONG ulCursorHeightPercent,
                            const bool fIsDoubleWidth,
                            const CursorType cursorType,
                            const bool fUseColor,
                            const COLORREF cursorColor) noexcept override;

        [[nodiscard]]
        HRESULT ClearCursor() noexcept override;

        [[nodiscard]]
        HRESULT UpdateDrawingBrushes(COLORREF const colorForeground,
                                     COLORREF const colorBackground,
                                     const WORD legacyColorAttribute,
                                     const bool isBold,
                                     bool const fIncludeBackgrounds) noexcept override;
        [[nodiscard]]
        HRESULT UpdateFont(const FontInfoDesired& fiFontInfoDesired, FontInfo& fiFontInfo) noexcept override;
        [[nodiscard]]
        HRESULT UpdateDpi(int const iDpi) noexcept override;
        [[nodiscard]]
        HRESULT UpdateViewport(const SMALL_RECT srNewViewport) noexcept override;

        [[nodiscard]]
        HRESULT GetProposedFont(const FontInfoDesired& fiFontInfoDesired, FontInfo& fiFontInfo, int const iDpi) noexcept override;

        SMALL_RECT GetDirtyRectInChars() override;
        [[nodiscard]]
        HRESULT GetFontSize(_Out_ COORD* const pFontSize) noexcept override;
        [[nodiscard]]
        HRESULT IsGlyphWideByFont(const std::wstring_view glyph, _Out_ bool* const pResult) noexcept override;

    protected:
        [[nodiscard]]
        HRESULT _DoUpdateTitle(_In_ const std::wstring& newTitle) noexcept override;

    private:
        HANDLE _hWddmConCtx;

        // Helpers
        void FreeResources(ULONG displayHeight);

        // Variables
        LONG _displayHeight;
        LONG _displayWidth;

        PCD_IO_ROW_INFORMATION *_displayState;

        WORD _currentLegacyColorAttribute;
    };
}
