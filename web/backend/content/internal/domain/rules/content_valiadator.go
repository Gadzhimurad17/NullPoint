package rules

import (
	"bytes"
	"errors"
	"io"
	"net/http"

	"github.com/Gagzhimurad17/NullPoint/web/backend/content/internal/domain/models"
)

const (
	MaxImageSize = 5 << 20   // 5 MB
	MaxVideoSize = 200 << 20 // 200 MB
)

type ValidatedFile struct {
	Reader   io.Reader
	FileType string
	Size     int64
}

var AllowedFileTypes = map[models.ContentType]map[string]struct{}{
	models.Avatar: {
		"image/jpeg": struct{}{},
		"image/png":  struct{}{},
	},
}

func validateSize(contentType models.ContentType, size int64) error {
	switch contentType {
	case models.Avatar:
		if size > MaxImageSize {
			return models.ErrFileTooLarge
		}
	default:
		return errors.New("unknown content type")
	}
	return nil
}

func ValidateContent(contentType models.ContentType, file io.Reader, size int64) (*ValidatedFile, error) {
	if size < 0 {
		return nil, models.ErrFileEmpty
	}

	if err := validateSize(contentType, size); err != nil {
		return nil, err
	}

	head := make([]byte, 512)
	n, err := file.Read(head)
	if err != nil && err != io.EOF {
		return nil, models.ErrContentNotFound
	}
	detectedContentType := http.DetectContentType(head[:n])
	allowedTypes, typeExists := AllowedFileTypes[contentType]
	_, allowed := allowedTypes[detectedContentType]
	if !typeExists || !allowed {
		return nil, models.ErrInvalidMimeType
	}

	restoredFile := io.MultiReader(bytes.NewReader(head[:n]), file)

	return &ValidatedFile{
		Reader:   restoredFile,
		FileType: detectedContentType,
		Size:     size,
	}, nil
}
