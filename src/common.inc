;; assumes we are in vblank
;; top-left tile number in a
;; top left screen location in de
;; clobbers af, de
put_img_16x16:
    push hl
    ld hl, $9800
    add hl, de
    ld de, $20
    ld [hl+], a
    inc a
checkjmp:
    ld [hl-], a
    add hl, de
    inc a
    ld [hl+], a
    inc a
    ld [hl], a
    pop hl
    ret

put_check:
    push hl
    ld hl, $9800
    add hl, de
    ld de, $20
    ld a, IMG_BLANK
    ld [hl+], a
    ld a, IMG_CHECK_1
    jr checkjmp

put_uparrow:
    push hl
    ld hl, $9800
    add hl, de
    ld de, $20
    ld a, IMG_ARROW_HEAD_0
    ld [hl+], a
    ld a, IMG_ARROW_HEAD_1
    ld [hl-], a
    add hl, de
    ld a, IMG_ARROW_TAIL_0
    ld [hl+], a
    ld a, IMG_ARROW_TAIL_1
    ld [hl], a
    pop hl
    ret

put_downarrow:
    push hl
    ld hl, $9800
    add hl, de
    ld de, $20
    ld a, IMG_ARROW_TAIL_0
    ld [hl+], a
    ld a, IMG_ARROW_TAIL_1
    ld [hl-], a
    add hl, de
    ld a, IMG_ARROW_HEAD_2
    ld [hl+], a
    ld a, IMG_ARROW_HEAD_3
    ld [hl], a
    pop hl
    ret

;; all except flags preserved
short_delay:
    push bc
    ld b, $ff
.loop:
    dec b
    jr nz, .loop
    pop bc
    ret

;; clobbers a
wait_vblank:
    push bc
    ld a, 144
    ld [$ff45], a
    ld b, $ff
.short_delay:
    dec b
    jr nz, .short_delay
wait_vblank_loop:
    ld a, [$ff41]
    and a, $04
    jr z, wait_vblank_loop
    pop bc
    ret